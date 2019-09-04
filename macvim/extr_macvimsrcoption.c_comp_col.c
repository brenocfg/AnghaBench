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
 void* Columns ; 
 void* ru_col ; 
 void* sc_col ; 

void
comp_col()
{
#if defined(FEAT_CMDL_INFO) && defined(FEAT_WINDOWS)
    int last_has_status = (p_ls == 2 || (p_ls == 1 && firstwin != lastwin));

    sc_col = 0;
    ru_col = 0;
    if (p_ru)
    {
#ifdef FEAT_STL_OPT
	ru_col = (ru_wid ? ru_wid : COL_RULER) + 1;
#else
	ru_col = COL_RULER + 1;
#endif
	/* no last status line, adjust sc_col */
	if (!last_has_status)
	    sc_col = ru_col;
    }
    if (p_sc)
    {
	sc_col += SHOWCMD_COLS;
	if (!p_ru || last_has_status)	    /* no need for separating space */
	    ++sc_col;
    }
    sc_col = Columns - sc_col;
    ru_col = Columns - ru_col;
    if (sc_col <= 0)		/* screen too narrow, will become a mess */
	sc_col = 1;
    if (ru_col <= 0)
	ru_col = 1;
#else
    sc_col = Columns;
    ru_col = Columns;
#endif
}