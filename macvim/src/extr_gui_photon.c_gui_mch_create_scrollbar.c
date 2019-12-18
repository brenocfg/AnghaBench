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
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {void* id; TYPE_1__* wp; } ;
typedef  TYPE_2__ scrollbar_T ;
struct TYPE_8__ {int /*<<< orphan*/  vimContainer; int /*<<< orphan*/  vimPanelGroup; } ;
struct TYPE_6__ {TYPE_2__* w_scrollbars; } ;
typedef  int /*<<< orphan*/  PtArg_t ;

/* Variables and functions */
 int /*<<< orphan*/  PtAddCallback (void*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_2__*) ; 
 void* PtCreateWidget (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PtScrollbar ; 
 int /*<<< orphan*/  PtSetArg (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  Pt_ARG_ANCHOR_FLAGS ; 
 int /*<<< orphan*/  Pt_ARG_FLAGS ; 
 int /*<<< orphan*/  Pt_ARG_ORIENTATION ; 
 int /*<<< orphan*/  Pt_ARG_SCROLLBAR_FLAGS ; 
 int Pt_BOTTOM_ANCHORED_BOTTOM ; 
 int /*<<< orphan*/  Pt_CB_SCROLLBAR_MOVE ; 
 int Pt_DELAY_REALIZE ; 
 int Pt_GETS_FOCUS ; 
 int Pt_HORIZONTAL ; 
 int Pt_IS_ANCHORED ; 
 int Pt_LEFT_ANCHORED_LEFT ; 
 int Pt_RIGHT_ANCHORED_RIGHT ; 
 int Pt_SCROLLBAR_SHOW_ARROWS ; 
 int Pt_TOP_ANCHORED_TOP ; 
 int Pt_VERTICAL ; 
 int SBAR_HORIZ ; 
 size_t SBAR_LEFT ; 
 int anchor_flags ; 
 TYPE_4__ gui ; 
 int /*<<< orphan*/  gui_ph_handle_scrollbar ; 

void
gui_mch_create_scrollbar(scrollbar_T *sb, int orient)
{
    int	    n = 0;
/*    int	    anchor_flags = 0;*/
    PtArg_t args[4];

    /*
     * Stop the scrollbar from being realized when the parent
     * is realized, so it can be explicitly realized by vim.
     *
     * Also, don't let the scrollbar get focus
     */
    PtSetArg(&args[ n++ ], Pt_ARG_FLAGS, Pt_DELAY_REALIZE,
	    Pt_DELAY_REALIZE | Pt_GETS_FOCUS);
    PtSetArg(&args[ n++ ], Pt_ARG_SCROLLBAR_FLAGS, Pt_SCROLLBAR_SHOW_ARROWS, 0);
#if 0
    /* Don't need this anchoring for the scrollbars */
    if (orient == SBAR_HORIZ)
    {
	anchor_flags = Pt_BOTTOM_ANCHORED_BOTTOM |
	    Pt_LEFT_ANCHORED_LEFT | Pt_RIGHT_ANCHORED_RIGHT;
    }
    else
    {
	anchor_flags = Pt_BOTTOM_ANCHORED_BOTTOM | Pt_TOP_ANCHORED_TOP;
	if (sb->wp != NULL)
	{
	    if (sb == &sb->wp->w_scrollbars[ SBAR_LEFT ])
		anchor_flags |= Pt_LEFT_ANCHORED_LEFT;
	    else
		anchor_flags |= Pt_RIGHT_ANCHORED_RIGHT;
	}
    }
    PtSetArg(&args[ n++ ], Pt_ARG_ANCHOR_FLAGS, anchor_flags, Pt_IS_ANCHORED);
#endif
    PtSetArg(&args[ n++ ], Pt_ARG_ORIENTATION,
	    (orient == SBAR_HORIZ) ? Pt_HORIZONTAL : Pt_VERTICAL, 0);
#ifdef USE_PANEL_GROUP
    sb->id = PtCreateWidget(PtScrollbar, gui.vimPanelGroup, n, args);
#else
    sb->id = PtCreateWidget(PtScrollbar, gui.vimContainer, n, args);
#endif

    PtAddCallback(sb->id, Pt_CB_SCROLLBAR_MOVE, gui_ph_handle_scrollbar, sb);
}