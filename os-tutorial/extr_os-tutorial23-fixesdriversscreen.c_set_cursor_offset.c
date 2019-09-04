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
 int /*<<< orphan*/  REG_SCREEN_CTRL ; 
 int /*<<< orphan*/  REG_SCREEN_DATA ; 
 int /*<<< orphan*/  port_byte_out (int /*<<< orphan*/ ,int) ; 

void set_cursor_offset(int offset) {
    /* Similar to get_cursor_offset, but instead of reading we write data */
    offset /= 2;
    port_byte_out(REG_SCREEN_CTRL, 14);
    port_byte_out(REG_SCREEN_DATA, (uint8_t)(offset >> 8));
    port_byte_out(REG_SCREEN_CTRL, 15);
    port_byte_out(REG_SCREEN_DATA, (uint8_t)(offset & 0xff));
}