#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ col; } ;
struct TYPE_4__ {TYPE_1__ w_cursor; } ;

/* Variables and functions */
 int INSERT ; 
 scalar_t__ NUL ; 
 int State ; 
 TYPE_2__* curwin ; 
 int /*<<< orphan*/  dec_cursor () ; 
 scalar_t__ gchar_cursor () ; 
 scalar_t__ restart_edit ; 

void
adjust_cursor_eol()
{
    if (curwin->w_cursor.col > 0
	    && gchar_cursor() == NUL
#ifdef FEAT_VIRTUALEDIT
	    && (ve_flags & VE_ONEMORE) == 0
#endif
	    && !(restart_edit || (State & INSERT)))
    {
	/* Put the cursor on the last character in the line. */
	dec_cursor();

#ifdef FEAT_VIRTUALEDIT
	if (ve_flags == VE_ALL)
	{
	    colnr_T	    scol, ecol;

	    /* Coladd is set to the width of the last character. */
	    getvcol(curwin, &curwin->w_cursor, &scol, NULL, &ecol);
	    curwin->w_cursor.coladd = ecol - scol + 1;
	}
#endif
    }
}