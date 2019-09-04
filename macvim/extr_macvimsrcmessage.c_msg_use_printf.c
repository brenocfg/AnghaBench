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
 int /*<<< orphan*/  msg_check_screen () ; 
 scalar_t__ swapping_screen () ; 
 int /*<<< orphan*/  termcap_active ; 

int
msg_use_printf()
{
    return (!msg_check_screen()
#if defined(WIN3264) && !defined(FEAT_GUI_MSWIN)
	    || !termcap_active
#endif
	    || (swapping_screen() && !termcap_active)
	       );
}