#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ colnr_T ;
typedef  int /*<<< orphan*/  char_u ;
struct TYPE_4__ {int /*<<< orphan*/  ml_line_count; } ;
struct TYPE_6__ {TYPE_1__ b_ml; } ;
struct TYPE_5__ {int /*<<< orphan*/  w_cursor; } ;

/* Variables and functions */
 int /*<<< orphan*/  AppendToRedobuff (int /*<<< orphan*/ *) ; 
 int FAIL ; 
 void* FALSE ; 
 int /*<<< orphan*/  Insstart ; 
 scalar_t__ Insstart_textlen ; 
 scalar_t__ OK ; 
 int /*<<< orphan*/  ResetRedobuff () ; 
 int State ; 
 int VREPLACE_FLAG ; 
 scalar_t__ ai_col ; 
 void* arrow_used ; 
 TYPE_3__* curbuf ; 
 TYPE_2__* curwin ; 
 int /*<<< orphan*/  foldOpenCursor () ; 
 void* ins_need_undo ; 
 scalar_t__ linetabsize (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ml_get_curline () ; 
 int new_insert_skip ; 
 int /*<<< orphan*/  orig_line_count ; 
 scalar_t__ u_save_cursor () ; 
 int vr_lines_changed ; 

int
stop_arrow()
{
    if (arrow_used)
    {
	if (u_save_cursor() == OK)
	{
	    arrow_used = FALSE;
	    ins_need_undo = FALSE;
	}
	Insstart = curwin->w_cursor;	/* new insertion starts here */
	Insstart_textlen = (colnr_T)linetabsize(ml_get_curline());
	ai_col = 0;
#ifdef FEAT_VREPLACE
	if (State & VREPLACE_FLAG)
	{
	    orig_line_count = curbuf->b_ml.ml_line_count;
	    vr_lines_changed = 1;
	}
#endif
	ResetRedobuff();
	AppendToRedobuff((char_u *)"1i");   /* pretend we start an insertion */
	new_insert_skip = 2;
    }
    else if (ins_need_undo)
    {
	if (u_save_cursor() == OK)
	    ins_need_undo = FALSE;
    }

#ifdef FEAT_FOLDING
    /* Always open fold at the cursor line when inserting something. */
    foldOpenCursor();
#endif

    return (arrow_used || ins_need_undo ? FAIL : OK);
}