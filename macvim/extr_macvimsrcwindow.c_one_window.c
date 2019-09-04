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
 scalar_t__ firstwin ; 
 scalar_t__ lastwin ; 

int
one_window()
{
#ifdef FEAT_AUTOCMD
    win_T	*wp;
    int		seen_one = FALSE;

    FOR_ALL_WINDOWS(wp)
    {
	if (wp != aucmd_win)
	{
	    if (seen_one)
		return FALSE;
	    seen_one = TRUE;
	}
    }
    return TRUE;
#else
    return firstwin == lastwin;
#endif
}