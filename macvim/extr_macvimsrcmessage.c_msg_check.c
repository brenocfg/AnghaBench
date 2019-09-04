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
 int Rows ; 
 void* TRUE ; 
 scalar_t__ msg_col ; 
 int msg_row ; 
 void* need_wait_return ; 
 void* redraw_cmdline ; 
 scalar_t__ sc_col ; 

void
msg_check()
{
    if (msg_row == Rows - 1 && msg_col >= sc_col)
    {
	need_wait_return = TRUE;
	redraw_cmdline = TRUE;
    }
}