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
 int TRUE ; 

int
only_one_window()
{
#ifdef FEAT_WINDOWS
    int		count = 0;
    win_T	*wp;

    /* If there is another tab page there always is another window. */
    if (first_tabpage->tp_next != NULL)
	return FALSE;

    for (wp = firstwin; wp != NULL; wp = wp->w_next)
	if (wp->w_buffer != NULL
		&& (!((wp->w_buffer->b_help && !curbuf->b_help)
# ifdef FEAT_QUICKFIX
		    || wp->w_p_pvw
# endif
	     ) || wp == curwin)
# ifdef FEAT_AUTOCMD
		&& wp != aucmd_win
# endif
	   )
	    ++count;
    return (count <= 1);
#else
    return TRUE;
#endif
}