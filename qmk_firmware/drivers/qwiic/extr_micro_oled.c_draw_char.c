#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  scalar_t__ uint8_t ;
typedef  scalar_t__ uint16_t ;

/* Variables and functions */
 scalar_t__ FONTHEADERSIZE ; 
 scalar_t__ TOTALFONTS ; 
 int /*<<< orphan*/  draw_pixel (scalar_t__,scalar_t__,int,scalar_t__) ; 
 scalar_t__* fonts_pointer ; 
 int pgm_read_byte (scalar_t__) ; 

void draw_char(uint8_t x, uint8_t y, uint8_t c, uint8_t color, uint8_t mode, uint8_t font) {
    // TODO - New routine to take font of any height, at the moment limited to font height in multiple of 8 pixels

    uint8_t  rowsToDraw, row, tempC;
    uint8_t  i, j, temp;
    uint16_t charPerBitmapRow, charColPositionOnBitmap, charRowPositionOnBitmap, charBitmapStartPosition;

    if ((font >= TOTALFONTS) || (font < 0)) return;

    uint8_t  fontType      = font;
    uint8_t  fontWidth     = pgm_read_byte(fonts_pointer[fontType] + 0);
    uint8_t  fontHeight    = pgm_read_byte(fonts_pointer[fontType] + 1);
    uint8_t  fontStartChar = pgm_read_byte(fonts_pointer[fontType] + 2);
    uint8_t  fontTotalChar = pgm_read_byte(fonts_pointer[fontType] + 3);
    uint16_t fontMapWidth  = (pgm_read_byte(fonts_pointer[fontType] + 4) * 100) + pgm_read_byte(fonts_pointer[fontType] + 5);  // two bytes values into integer 16

    if ((c < fontStartChar) || (c > (fontStartChar + fontTotalChar - 1)))  // no bitmap for the required c
        return;

    tempC = c - fontStartChar;

    // each row (in datasheet is call page) is 8 bits high, 16 bit high character will have 2 rows to be drawn
    rowsToDraw = fontHeight / 8;  // 8 is LCD's page size, see SSD1306 datasheet
    if (rowsToDraw <= 1) rowsToDraw = 1;

    // the following draw function can draw anywhere on the screen, but SLOW pixel by pixel draw
    if (rowsToDraw == 1) {
        for (i = 0; i < fontWidth + 1; i++) {
            if (i == fontWidth)  // this is done in a weird way because for 5x7 font, there is no margin, this code add a margin after col 5
                temp = 0;
            else
                temp = pgm_read_byte(fonts_pointer[fontType] + FONTHEADERSIZE + (tempC * fontWidth) + i);

            for (j = 0; j < 8; j++) {  // 8 is the LCD's page height (see datasheet for explanation)
                if (temp & 0x1) {
                    draw_pixel(x + i, y + j, color, mode);
                } else {
                    draw_pixel(x + i, y + j, !color, mode);
                }

                temp >>= 1;
            }
        }
        return;
    }

    // font height over 8 bit
    // take character "0" ASCII 48 as example
    charPerBitmapRow        = fontMapWidth / fontWidth;         // 256/8 =32 char per row
    charColPositionOnBitmap = tempC % charPerBitmapRow;         // =16
    charRowPositionOnBitmap = (int)(tempC / charPerBitmapRow);  // =1
    charBitmapStartPosition = (charRowPositionOnBitmap * fontMapWidth * (fontHeight / 8)) + (charColPositionOnBitmap * fontWidth);

    // each row on LCD is 8 bit height (see datasheet for explanation)
    for (row = 0; row < rowsToDraw; row++) {
        for (i = 0; i < fontWidth; i++) {
            temp = pgm_read_byte(fonts_pointer[fontType] + FONTHEADERSIZE + (charBitmapStartPosition + i + (row * fontMapWidth)));
            for (j = 0; j < 8; j++) {  // 8 is the LCD's page height (see datasheet for explanation)
                if (temp & 0x1) {
                    draw_pixel(x + i, y + j + (row * 8), color, mode);
                } else {
                    draw_pixel(x + i, y + j + (row * 8), !color, mode);
                }
                temp >>= 1;
            }
        }
    }
}