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
 int /*<<< orphan*/  check_arg_idx (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  curwin ; 

__attribute__((used)) static void
alist_check_arg_idx()
{
#ifdef FEAT_WINDOWS
    win_T	*win;
    tabpage_T	*tp;

    FOR_ALL_TAB_WINDOWS(tp, win)
	if (win->w_alist == curwin->w_alist)
	    check_arg_idx(win);
#else
    check_arg_idx(curwin);
#endif
}