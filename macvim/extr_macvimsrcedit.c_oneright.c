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
typedef  scalar_t__ char_u ;
struct TYPE_3__ {int col; } ;
struct TYPE_4__ {int /*<<< orphan*/  w_set_curswant; TYPE_1__ w_cursor; } ;

/* Variables and functions */
 int FAIL ; 
 scalar_t__ NUL ; 
 int OK ; 
 int /*<<< orphan*/  TRUE ; 
 TYPE_2__* curwin ; 
 scalar_t__* ml_get_cursor () ; 

int
oneright()
{
    char_u	*ptr;
    int		l;

#ifdef FEAT_VIRTUALEDIT
    if (virtual_active())
    {
	pos_T	prevpos = curwin->w_cursor;

	/* Adjust for multi-wide char (excluding TAB) */
	ptr = ml_get_cursor();
	coladvance(getviscol() + ((*ptr != TAB && vim_isprintc(
# ifdef FEAT_MBYTE
			    (*mb_ptr2char)(ptr)
# else
			    *ptr
# endif
			    ))
		    ? ptr2cells(ptr) : 1));
	curwin->w_set_curswant = TRUE;
	/* Return OK if the cursor moved, FAIL otherwise (at window edge). */
	return (prevpos.col != curwin->w_cursor.col
		    || prevpos.coladd != curwin->w_cursor.coladd) ? OK : FAIL;
    }
#endif

    ptr = ml_get_cursor();
    if (*ptr == NUL)
	return FAIL;	    /* already at the very end */

#ifdef FEAT_MBYTE
    if (has_mbyte)
	l = (*mb_ptr2len)(ptr);
    else
#endif
	l = 1;

    /* move "l" bytes right, but don't end up on the NUL, unless 'virtualedit'
     * contains "onemore". */
    if (ptr[l] == NUL
#ifdef FEAT_VIRTUALEDIT
	    && (ve_flags & VE_ONEMORE) == 0
#endif
	    )
	return FAIL;
    curwin->w_cursor.col += l;

    curwin->w_set_curswant = TRUE;
    return OK;
}