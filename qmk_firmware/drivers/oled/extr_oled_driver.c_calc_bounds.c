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
 int NOP ; 
 int OLED_BLOCK_SIZE ; 
 int OLED_COLUMN_OFFSET ; 
 int OLED_DISPLAY_WIDTH ; 
 int PAM_PAGE_ADDR ; 
 int PAM_SETCOLUMN_LSB ; 
 int PAM_SETCOLUMN_MSB ; 

__attribute__((used)) static void calc_bounds(uint8_t update_start, uint8_t *cmd_array) {
    // Calculate commands to set memory addressing bounds.
    uint8_t start_page   = OLED_BLOCK_SIZE * update_start / OLED_DISPLAY_WIDTH;
    uint8_t start_column = OLED_BLOCK_SIZE * update_start % OLED_DISPLAY_WIDTH;
#if (OLED_IC == OLED_IC_SH1106)
    // Commands for Page Addressing Mode. Sets starting page and column; has no end bound.
    // Column value must be split into high and low nybble and sent as two commands.
    cmd_array[0] = PAM_PAGE_ADDR | start_page;
    cmd_array[1] = PAM_SETCOLUMN_LSB | ((OLED_COLUMN_OFFSET + start_column) & 0x0f);
    cmd_array[2] = PAM_SETCOLUMN_MSB | ((OLED_COLUMN_OFFSET + start_column) >> 4 & 0x0f);
    cmd_array[3] = NOP;
    cmd_array[4] = NOP;
    cmd_array[5] = NOP;
#else
    // Commands for use in Horizontal Addressing mode.
    cmd_array[1] = start_column;
    cmd_array[4] = start_page;
    cmd_array[2] = (OLED_BLOCK_SIZE + OLED_DISPLAY_WIDTH - 1) % OLED_DISPLAY_WIDTH + cmd_array[1];
    cmd_array[5] = (OLED_BLOCK_SIZE + OLED_DISPLAY_WIDTH - 1) / OLED_DISPLAY_WIDTH - 1;
#endif
}