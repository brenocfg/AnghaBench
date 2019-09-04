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
struct TYPE_4__ {TYPE_1__ w_cursor; int /*<<< orphan*/  w_set_curswant; } ;

/* Variables and functions */
 int FAIL ; 
 int OK ; 
 int /*<<< orphan*/  TRUE ; 
 TYPE_2__* curwin ; 

int
oneleft()
{
#ifdef FEAT_VIRTUALEDIT
    if (virtual_active())
    {
	int width;
	int v = getviscol();

	if (v == 0)
	    return FAIL;

# ifdef FEAT_LINEBREAK
	/* We might get stuck on 'showbreak', skip over it. */
	width = 1;
	for (;;)
	{
	    coladvance(v - width);
	    /* getviscol() is slow, skip it when 'showbreak' is empty,
	     * 'breakindent' is not set and there are no multi-byte
	     * characters */
	    if ((*p_sbr == NUL && !curwin->w_p_bri
#  ifdef FEAT_MBYTE
			&& !has_mbyte
#  endif
			) || getviscol() < v)
		break;
	    ++width;
	}
# else
	coladvance(v - 1);
# endif

	if (curwin->w_cursor.coladd == 1)
	{
	    char_u *ptr;

	    /* Adjust for multi-wide char (not a TAB) */
	    ptr = ml_get_cursor();
	    if (*ptr != TAB && vim_isprintc(
#  ifdef FEAT_MBYTE
			    (*mb_ptr2char)(ptr)
#  else
			    *ptr
#  endif
			    ) && ptr2cells(ptr) > 1)
		curwin->w_cursor.coladd = 0;
	}

	curwin->w_set_curswant = TRUE;
	return OK;
    }
#endif

    if (curwin->w_cursor.col == 0)
	return FAIL;

    curwin->w_set_curswant = TRUE;
    --curwin->w_cursor.col;

#ifdef FEAT_MBYTE
    /* if the character on the left of the current cursor is a multi-byte
     * character, move to its first byte */
    if (has_mbyte)
	mb_adjust_cursor();
#endif
    return OK;
}