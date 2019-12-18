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
struct TYPE_3__ {int lnum; scalar_t__ col; } ;
struct TYPE_4__ {int /*<<< orphan*/  w_set_curswant; TYPE_1__ w_cursor; } ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int FDO_HOR ; 
 scalar_t__ KeyTyped ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  bck_word (long,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_2__* curwin ; 
 int fdo_flags ; 
 int /*<<< orphan*/  foldOpenCursor () ; 
 int /*<<< orphan*/  start_arrow (TYPE_1__*) ; 
 int /*<<< orphan*/  undisplay_dollar () ; 
 int /*<<< orphan*/  vim_beep () ; 

__attribute__((used)) static void
ins_s_left()
{
#ifdef FEAT_FOLDING
    if ((fdo_flags & FDO_HOR) && KeyTyped)
	foldOpenCursor();
#endif
    undisplay_dollar();
    if (curwin->w_cursor.lnum > 1 || curwin->w_cursor.col > 0)
    {
	start_arrow(&curwin->w_cursor);
	(void)bck_word(1L, FALSE, FALSE);
	curwin->w_set_curswant = TRUE;
    }
    else
	vim_beep();
}