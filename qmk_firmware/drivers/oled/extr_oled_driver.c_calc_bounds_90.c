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
 int OLED_BLOCK_SIZE ; 
 int OLED_DISPLAY_HEIGHT ; 

__attribute__((used)) static void calc_bounds_90(uint8_t update_start, uint8_t *cmd_array) {
    cmd_array[1] = OLED_BLOCK_SIZE * update_start / OLED_DISPLAY_HEIGHT * 8;
    cmd_array[4] = OLED_BLOCK_SIZE * update_start % OLED_DISPLAY_HEIGHT;
    cmd_array[2] = (OLED_BLOCK_SIZE + OLED_DISPLAY_HEIGHT - 1) / OLED_DISPLAY_HEIGHT * 8 - 1 + cmd_array[1];
    ;
    cmd_array[5] = (OLED_BLOCK_SIZE + OLED_DISPLAY_HEIGHT - 1) % OLED_DISPLAY_HEIGHT / 8;
}