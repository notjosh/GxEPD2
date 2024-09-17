// Display Library for SPI e-paper panels from Dalian Good Display and boards from Waveshare.
// Requires HW SPI and Adafruit_GFX. Caution: the e-paper panels require 3.3V supply AND data lines!
//
// based on Demo Example from Good Display:https://www.good-display.com/comp/xcompanyFile/downloadNew.do?appId=24&fid=2134&id=1555
// Panel: GDEY0579F51 : https://www.good-display.com/product/570.html
// Panel specs: https://v4.cecdn.yun300.cn/100001_1909185148/GDEY0579F51.pdf
// Controller: HX8717 : https://v4.cecdn.yun300.cn/100001_1909185148/HX8717-A_DS_preliminary_v01_230417.pdf
//
// Author: Jean-Marc Zingg
//
// Version: see library.properties
//
// Library: https://github.com/ZinggJM/GxEPD2

#ifndef _GxEPD2_0579c_GDEY0579F51_H_
#define _GxEPD2_0579c_GDEY0579F51_H_

#include "../GxEPD2_EPD.h"

class GxEPD2_0579c_GDEY0579F51 : public GxEPD2_EPD
{
  public:
    // attributes
    static const uint16_t WIDTH = 792;
    static const uint16_t WIDTH_VISIBLE = WIDTH;
    static const uint16_t HEIGHT = 272;
    static const GxEPD2::Panel panel = GxEPD2::GDEY0579F51;
    static const bool hasColor = true;
    static const bool hasPartialUpdate = true;
    static const bool hasFastPartialUpdate = false;
    static const uint16_t power_on_time = 100; // ms, e.g. 64001us
    static const uint16_t power_off_time = 100; // ms, e.g. 61001us
    static const uint16_t full_refresh_time = 21000; // ms, e.g. 20070999us
    static const uint16_t partial_refresh_time = 21000; // ms, e.g. 20070999us
    // constructor
    GxEPD2_0579c_GDEY0579F51(int16_t cs, int16_t dc, int16_t rst, int16_t busy);
    // methods (virtual)
    //  Support for Bitmaps (Sprites) to Controller Buffer and to Screen
    void clearScreen(uint8_t value = 0xFF); // init controller memory and screen (default white)
    void clearScreen(uint8_t black_value, uint8_t color_value); // init controller memory and screen
    void writeScreenBuffer(uint8_t value = 0xFF); // init controller memory (default white)
    void writeScreenBuffer(uint8_t black_value, uint8_t color_value); // init controller memory
    // write to controller memory, without screen refresh; x and w should be multiple of 8
    void writeImage(const uint8_t bitmap[], int16_t x, int16_t y, int16_t w, int16_t h, bool invert = false, bool mirror_y = false, bool pgm = false);
    void writeImagePart(const uint8_t bitmap[], int16_t x_part, int16_t y_part, int16_t w_bitmap, int16_t h_bitmap,
                        int16_t x, int16_t y, int16_t w, int16_t h, bool invert = false, bool mirror_y = false, bool pgm = false);
    void writeImage(const uint8_t* black, const uint8_t* color, int16_t x, int16_t y, int16_t w, int16_t h, bool invert = false, bool mirror_y = false, bool pgm = false);
    void writeImagePart(const uint8_t* black, const uint8_t* color, int16_t x_part, int16_t y_part, int16_t w_bitmap, int16_t h_bitmap,
                        int16_t x, int16_t y, int16_t w, int16_t h, bool invert = false, bool mirror_y = false, bool pgm = false);
    // write sprite of native data to controller memory, without screen refresh; x and w should be multiple of 8
    void writeNative(const uint8_t* data1, const uint8_t* data2, int16_t x, int16_t y, int16_t w, int16_t h, bool invert = false, bool mirror_y = false, bool pgm = false);
    void writeNativePart(const uint8_t* data1, const uint8_t* data2, int16_t x_part, int16_t y_part, int16_t w_bitmap, int16_t h_bitmap,
                        int16_t x, int16_t y, int16_t w, int16_t h, bool invert = false, bool mirror_y = false, bool pgm = false);
    // write to controller memory, with screen refresh; x and w should be multiple of 8
    void drawImage(const uint8_t bitmap[], int16_t x, int16_t y, int16_t w, int16_t h, bool invert = false, bool mirror_y = false, bool pgm = false);
    void drawImagePart(const uint8_t bitmap[], int16_t x_part, int16_t y_part, int16_t w_bitmap, int16_t h_bitmap,
                       int16_t x, int16_t y, int16_t w, int16_t h, bool invert = false, bool mirror_y = false, bool pgm = false);
    void drawImage(const uint8_t* black, const uint8_t* color, int16_t x, int16_t y, int16_t w, int16_t h, bool invert = false, bool mirror_y = false, bool pgm = false);
    void drawImagePart(const uint8_t* black, const uint8_t* color, int16_t x_part, int16_t y_part, int16_t w_bitmap, int16_t h_bitmap,
                       int16_t x, int16_t y, int16_t w, int16_t h, bool invert = false, bool mirror_y = false, bool pgm = false);
    // write sprite of native data to controller memory, with screen refresh; x and w should be multiple of 8
    void drawNative(const uint8_t* data1, const uint8_t* data2, int16_t x, int16_t y, int16_t w, int16_t h, bool invert = false, bool mirror_y = false, bool pgm = false);
    void refresh(bool partial_update_mode = false); // screen refresh from controller memory to full screen
    void refresh(int16_t x, int16_t y, int16_t w, int16_t h); // screen refresh from controller memory, partial screen
    void powerOff(); // turns off generation of panel driving voltages, avoids screen fading over time
    void hibernate(); // turns powerOff() and sets controller to deep sleep for minimum power use, ONLY if wakeable by RST (rst >= 0)
    void setPaged(); // for GxEPD2_154c paged workaround, also for 4-color for use with hasPartialUpdate = false
  private:
    void _writeLineFromImage(const uint8_t* black, const uint8_t* color, int16_t x, int16_t y, int16_t w, int16_t wbb, bool invert, bool pgm, bool lowside, bool trf);
    void _writeDataFromImage(const uint8_t* black, const uint8_t* color, int16_t x, int16_t y, int16_t w, int16_t h, int16_t wbb, int16_t hb, bool invert, bool mirror_y, bool pgm, bool lowside);
    void _writeLineFromNative(const uint8_t* native, int16_t x, int16_t y, int16_t w, int16_t wbb, bool invert, bool pgm, bool trf);
    void _writeDataFromNative(const uint8_t* native, int16_t x, int16_t y, int16_t w, int16_t h, int16_t wbb, int16_t hb, bool invert, bool mirror_y, bool pgm);
    void _refresh(bool partial_update_mode);
    void _setPartialRamAreaMaster(uint16_t x, uint16_t y, uint16_t w, uint16_t h, bool partial_mode = true);
    void _setPartialRamAreaSlave(uint16_t x, uint16_t y, uint16_t w, uint16_t h, bool partial_mode = true);
    void _setPartialRamAreaBoth(uint16_t x, uint16_t y, uint16_t w, uint16_t h, bool partial_mode = true);
    void _setPartialRamArea(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint8_t select = 0x00, bool partial_mode = true);
    void _PowerOn();
    void _PowerOff();
    void _InitDisplay();
    void _ReInitDisplay();
  private:
    bool _paged;
    bool _needs_re_init;
};

#endif
