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
 int LCDHEIGHT ; 
 int LCDWIDTH ; 
 scalar_t__* micro_oled_screen_buffer ; 
 scalar_t__* micro_oled_screen_current ; 
 int /*<<< orphan*/  send_data (scalar_t__) ; 
 int /*<<< orphan*/  set_column_address (int) ; 
 int /*<<< orphan*/  set_page_address (int) ; 

void send_buffer(void) {
    uint8_t i, j;

    uint8_t page_addr = 0xFF;
    for (i = 0; i < LCDHEIGHT / 8; i++) {
        uint8_t col_addr = 0xFF;
        for (j = 0; j < LCDWIDTH; j++) {
            if (micro_oled_screen_buffer[i * LCDWIDTH + j] != micro_oled_screen_current[i * LCDWIDTH + j]) {
                if (page_addr != i) {
                    set_page_address(i);
                }
                if (col_addr != j) {
                    set_column_address(j);
                }
                send_data(micro_oled_screen_buffer[i * LCDWIDTH + j]);
                micro_oled_screen_current[i * LCDWIDTH + j] = micro_oled_screen_buffer[i * LCDWIDTH + j];
                col_addr                                    = j + 1;
            }
        }
    }
}