#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  long_u ;
typedef  int /*<<< orphan*/  linenr_T ;
typedef  int /*<<< orphan*/  colnr_T ;
typedef  int /*<<< orphan*/  char_u ;
struct TYPE_5__ {scalar_t__ ml_line_count; } ;
struct TYPE_8__ {scalar_t__ b_u_line_lnum; int /*<<< orphan*/  b_u_line_colnr; int /*<<< orphan*/ * b_u_line_ptr; TYPE_1__ b_ml; } ;
struct TYPE_6__ {scalar_t__ lnum; int /*<<< orphan*/  col; } ;
struct TYPE_7__ {TYPE_2__ w_cursor; } ;

/* Variables and functions */
 scalar_t__ FAIL ; 
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  beep_flush () ; 
 int /*<<< orphan*/  changed_bytes (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  check_cursor_col () ; 
 TYPE_4__* curbuf ; 
 TYPE_3__* curwin ; 
 int /*<<< orphan*/  do_outofmem_msg (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ml_replace (scalar_t__,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * u_save_line (scalar_t__) ; 
 scalar_t__ u_savecommon (scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ undo_off ; 
 int /*<<< orphan*/  vim_free (int /*<<< orphan*/ *) ; 

void
u_undoline()
{
    colnr_T t;
    char_u  *oldp;

    if (undo_off)
	return;

    if (curbuf->b_u_line_ptr == NULL
			|| curbuf->b_u_line_lnum > curbuf->b_ml.ml_line_count)
    {
	beep_flush();
	return;
    }

    /* first save the line for the 'u' command */
    if (u_savecommon(curbuf->b_u_line_lnum - 1,
		       curbuf->b_u_line_lnum + 1, (linenr_T)0, FALSE) == FAIL)
	return;
    oldp = u_save_line(curbuf->b_u_line_lnum);
    if (oldp == NULL)
    {
	do_outofmem_msg((long_u)0);
	return;
    }
    ml_replace(curbuf->b_u_line_lnum, curbuf->b_u_line_ptr, TRUE);
    changed_bytes(curbuf->b_u_line_lnum, 0);
    vim_free(curbuf->b_u_line_ptr);
    curbuf->b_u_line_ptr = oldp;

    t = curbuf->b_u_line_colnr;
    if (curwin->w_cursor.lnum == curbuf->b_u_line_lnum)
	curbuf->b_u_line_colnr = curwin->w_cursor.col;
    curwin->w_cursor.col = t;
    curwin->w_cursor.lnum = curbuf->b_u_line_lnum;
    check_cursor_col();
}