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
 int FAIL ; 
 int OK ; 
 int /*<<< orphan*/  get_exe_name () ; 
 scalar_t__ isatty (int) ; 

int
mch_check_win(
    int argc,
    char **argv)
{
    get_exe_name();

#ifdef FEAT_GUI_W32
    return OK;	    /* GUI always has a tty */
#else
    if (isatty(1))
	return OK;
    return FAIL;
#endif
}