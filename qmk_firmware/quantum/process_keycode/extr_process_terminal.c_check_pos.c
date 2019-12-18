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

/* Variables and functions */
 scalar_t__ CMD_BUFF_SIZE ; 
 scalar_t__ current_cmd_buffer_pos ; 

void check_pos(void) {
    if (current_cmd_buffer_pos >= CMD_BUFF_SIZE) {  // if over the top, move it back down to the top of the buffer so you can climb back down...
        current_cmd_buffer_pos = CMD_BUFF_SIZE - 1;
    } else if (current_cmd_buffer_pos < 0) {  //...and if you fall under the bottom of the buffer, reset back to 0 so you can climb back up
        current_cmd_buffer_pos = 0;
    }
}