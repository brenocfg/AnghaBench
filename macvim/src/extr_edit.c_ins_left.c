#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_3__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int lnum; scalar_t__ col; } ;
typedef  TYPE_1__ pos_T ;
typedef  int /*<<< orphan*/  colnr_T ;
struct TYPE_5__ {int /*<<< orphan*/  w_set_curswant; TYPE_1__ w_cursor; } ;

/* Variables and functions */
 int FDO_HOR ; 
 scalar_t__ KeyTyped ; 
 scalar_t__ MAXCOL ; 
 scalar_t__ OK ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  coladvance (int /*<<< orphan*/ ) ; 
 TYPE_3__* curwin ; 
 int fdo_flags ; 
 int /*<<< orphan*/  foldOpenCursor () ; 
 int /*<<< orphan*/  im_is_preediting () ; 
 scalar_t__ oneleft () ; 
 int /*<<< orphan*/  p_ww ; 
 int /*<<< orphan*/  revins_chars ; 
 int /*<<< orphan*/  revins_legal ; 
 int revins_scol ; 
 int /*<<< orphan*/  start_arrow (TYPE_1__*) ; 
 int /*<<< orphan*/  undisplay_dollar () ; 
 int /*<<< orphan*/  vim_beep () ; 
 int /*<<< orphan*/ * vim_strchr (int /*<<< orphan*/ ,char) ; 

__attribute__((used)) static void
ins_left()
{
    pos_T	tpos;

#ifdef FEAT_FOLDING
    if ((fdo_flags & FDO_HOR) && KeyTyped)
	foldOpenCursor();
#endif
    undisplay_dollar();
    tpos = curwin->w_cursor;
    if (oneleft() == OK)
    {
#if defined(FEAT_XIM) && (defined(FEAT_GUI_GTK) || defined(FEAT_GUI_MACVIM))
	/* Only call start_arrow() when not busy with preediting, it will
	 * break undo.  K_LEFT is inserted in im_correct_cursor(). */
	if (!im_is_preediting())
#endif
	    start_arrow(&tpos);
#ifdef FEAT_RIGHTLEFT
	/* If exit reversed string, position is fixed */
	if (revins_scol != -1 && (int)curwin->w_cursor.col >= revins_scol)
	    revins_legal++;
	revins_chars++;
#endif
    }

    /*
     * if 'whichwrap' set for cursor in insert mode may go to
     * previous line
     */
    else if (vim_strchr(p_ww, '[') != NULL && curwin->w_cursor.lnum > 1)
    {
	start_arrow(&tpos);
	--(curwin->w_cursor.lnum);
	coladvance((colnr_T)MAXCOL);
	curwin->w_set_curswant = TRUE;	/* so we stay at the end */
    }
    else
	vim_beep();
}