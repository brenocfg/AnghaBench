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
 int /*<<< orphan*/  do_activate_getch2 () ; 
 int /*<<< orphan*/  do_deactivate_getch2 () ; 
 int /*<<< orphan*/  getch2_enabled ; 
 scalar_t__ getpgrp () ; 
 scalar_t__ tcgetpgrp (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tty_in ; 

__attribute__((used)) static void getch2_poll(void)
{
    if (!getch2_enabled)
        return;

    // check if stdin is in the foreground process group
    int newstatus = (tcgetpgrp(tty_in) == getpgrp());

    // and activate getch2 if it is, deactivate otherwise
    if (newstatus)
        do_activate_getch2();
    else
        do_deactivate_getch2();
}