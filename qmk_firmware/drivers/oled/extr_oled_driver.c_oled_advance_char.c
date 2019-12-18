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
typedef  int uint8_t ;
typedef  size_t uint16_t ;

/* Variables and functions */
 int OLED_FONT_WIDTH ; 
 size_t OLED_MATRIX_SIZE ; 
 int /*<<< orphan*/ * oled_buffer ; 
 int /*<<< orphan*/ * oled_cursor ; 
 size_t oled_rotation_width ; 

void oled_advance_char(void) {
    uint16_t nextIndex      = oled_cursor - &oled_buffer[0] + OLED_FONT_WIDTH;
    uint8_t  remainingSpace = oled_rotation_width - (nextIndex % oled_rotation_width);

    // Do we have enough space on the current line for the next character
    if (remainingSpace < OLED_FONT_WIDTH) {
        nextIndex += remainingSpace;
    }

    // Did we go out of bounds
    if (nextIndex >= OLED_MATRIX_SIZE) {
        nextIndex = 0;
    }

    // Update cursor position
    oled_cursor = &oled_buffer[nextIndex];
}