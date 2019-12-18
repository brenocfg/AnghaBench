#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ col; int /*<<< orphan*/  lnum; } ;
typedef  TYPE_2__ pos_T ;
struct TYPE_5__ {scalar_t__ coladd; scalar_t__ col; int /*<<< orphan*/  lnum; } ;
struct TYPE_7__ {int /*<<< orphan*/  w_set_curswant; TYPE_1__ w_cursor; } ;

/* Variables and functions */
 int /*<<< orphan*/  TRUE ; 
 TYPE_2__* buflist_findfpos (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  check_cursor_col () ; 
 int /*<<< orphan*/  check_cursor_lnum () ; 
 int /*<<< orphan*/  curbuf ; 
 TYPE_3__* curwin ; 
 scalar_t__ p_sol ; 

void
buflist_getfpos()
{
    pos_T	*fpos;

    fpos = buflist_findfpos(curbuf);

    curwin->w_cursor.lnum = fpos->lnum;
    check_cursor_lnum();

    if (p_sol)
	curwin->w_cursor.col = 0;
    else
    {
	curwin->w_cursor.col = fpos->col;
	check_cursor_col();
#ifdef FEAT_VIRTUALEDIT
	curwin->w_cursor.coladd = 0;
#endif
	curwin->w_set_curswant = TRUE;
    }
}