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

/* Variables and functions */
 int /*<<< orphan*/  HAS_FLAGS (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int OLED_DISPLAY_HEIGHT ; 
 int OLED_DISPLAY_WIDTH ; 
 int OLED_FONT_WIDTH ; 
 int /*<<< orphan*/  OLED_ROTATION_90 ; 
 int /*<<< orphan*/  oled_rotation ; 

uint8_t oled_max_chars(void) {
    if (!HAS_FLAGS(oled_rotation, OLED_ROTATION_90)) {
        return OLED_DISPLAY_WIDTH / OLED_FONT_WIDTH;
    }
    return OLED_DISPLAY_HEIGHT / OLED_FONT_WIDTH;
}