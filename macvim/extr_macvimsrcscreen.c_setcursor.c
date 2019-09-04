#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ w_wcol; scalar_t__ w_wrow; } ;

/* Variables and functions */
 scalar_t__ W_WINCOL (TYPE_1__*) ; 
 scalar_t__ W_WINROW (TYPE_1__*) ; 
 TYPE_1__* curwin ; 
 scalar_t__ redrawing () ; 
 int /*<<< orphan*/  validate_cursor () ; 
 int /*<<< orphan*/  windgoto (scalar_t__,scalar_t__) ; 

void
setcursor()
{
    if (redrawing())
    {
	validate_cursor();
	windgoto(W_WINROW(curwin) + curwin->w_wrow,
		W_WINCOL(curwin) + (
#ifdef FEAT_RIGHTLEFT
		/* With 'rightleft' set and the cursor on a double-wide
		 * character, position it on the leftmost column. */
		curwin->w_p_rl ? ((int)W_WIDTH(curwin) - curwin->w_wcol - (
# ifdef FEAT_MBYTE
			(has_mbyte
			   && (*mb_ptr2cells)(ml_get_cursor()) == 2
			   && vim_isprintc(gchar_cursor())) ? 2 :
# endif
			1)) :
#endif
							    curwin->w_wcol));
    }
}