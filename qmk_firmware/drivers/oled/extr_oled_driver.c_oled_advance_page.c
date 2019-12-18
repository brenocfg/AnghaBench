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
typedef  size_t uint8_t ;
typedef  size_t uint16_t ;

/* Variables and functions */
 size_t OLED_FONT_WIDTH ; 
 size_t OLED_MATRIX_SIZE ; 
 int /*<<< orphan*/ * oled_buffer ; 
 int /*<<< orphan*/ * oled_cursor ; 
 size_t oled_rotation_width ; 
 int /*<<< orphan*/  oled_write_char (char,int) ; 

void oled_advance_page(bool clearPageRemainder) {
    uint16_t index     = oled_cursor - &oled_buffer[0];
    uint8_t  remaining = oled_rotation_width - (index % oled_rotation_width);

    if (clearPageRemainder) {
        // Remaining Char count
        remaining = remaining / OLED_FONT_WIDTH;

        // Write empty character until next line
        while (remaining--) oled_write_char(' ', false);
    } else {
        // Next page index out of bounds?
        if (index + remaining >= OLED_MATRIX_SIZE) {
            index     = 0;
            remaining = 0;
        }

        oled_cursor = &oled_buffer[index + remaining];
    }
}