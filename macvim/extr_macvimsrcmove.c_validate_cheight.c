#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  lnum; } ;
struct TYPE_5__ {int w_valid; TYPE_1__ w_cursor; int /*<<< orphan*/  w_cline_height; } ;

/* Variables and functions */
 int VALID_CHEIGHT ; 
 int /*<<< orphan*/  check_cursor_moved (TYPE_2__*) ; 
 TYPE_2__* curwin ; 
 int /*<<< orphan*/  plines (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
validate_cheight()
{
    check_cursor_moved(curwin);
    if (!(curwin->w_valid & VALID_CHEIGHT))
    {
#ifdef FEAT_DIFF
	if (curwin->w_cursor.lnum == curwin->w_topline)
	    curwin->w_cline_height = plines_nofill(curwin->w_cursor.lnum)
							  + curwin->w_topfill;
	else
#endif
	    curwin->w_cline_height = plines(curwin->w_cursor.lnum);
#ifdef FEAT_FOLDING
	curwin->w_cline_folded = hasFolding(curwin->w_cursor.lnum, NULL, NULL);
#endif
	curwin->w_valid |= VALID_CHEIGHT;
    }
}