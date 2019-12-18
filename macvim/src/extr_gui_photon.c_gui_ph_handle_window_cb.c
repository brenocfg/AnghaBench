#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_4__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ushort_t ;
struct TYPE_7__ {int /*<<< orphan*/  vimContainer; int /*<<< orphan*/  vimWindow; } ;
struct TYPE_6__ {int event_f; int /*<<< orphan*/  event_state; } ;
struct TYPE_5__ {TYPE_2__* cbdata; } ;
typedef  int /*<<< orphan*/  PtWidget_t ;
typedef  TYPE_1__ PtCallbackInfo_t ;
typedef  TYPE_2__ PhWindowEvent_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  MOUSE_SHOW ; 
#define  Ph_WM_CLOSE 130 
 int /*<<< orphan*/  Ph_WM_EVSTATE_FOCUS ; 
#define  Ph_WM_FOCUS 129 
#define  Ph_WM_RESIZE 128 
 int /*<<< orphan*/  PtContainerRelease (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PtEndFlux (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PtGetResource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ **,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Pt_ARG_HEIGHT ; 
 int /*<<< orphan*/  Pt_ARG_WIDTH ; 
 int Pt_CONTINUE ; 
 int /*<<< orphan*/  RESIZE_BOTH ; 
 int /*<<< orphan*/  TRUE ; 
 TYPE_4__ gui ; 
 int /*<<< orphan*/  gui_focus_change (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gui_mch_mousehide (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gui_mch_start_blink () ; 
 int /*<<< orphan*/  gui_mch_stop_blink () ; 
 int /*<<< orphan*/  gui_resize_shell (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gui_set_shellsize (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gui_shell_closed () ; 
 int /*<<< orphan*/  is_ignore_draw ; 
 scalar_t__ pg_margin_bottom ; 
 scalar_t__ pg_margin_left ; 
 scalar_t__ pg_margin_right ; 
 scalar_t__ pg_margin_top ; 

__attribute__((used)) static int
gui_ph_handle_window_cb(PtWidget_t *widget, void *data, PtCallbackInfo_t *info)
{
    PhWindowEvent_t *we = info->cbdata;
    ushort_t *width, *height;

    switch (we->event_f) {
	case Ph_WM_CLOSE:
	    gui_shell_closed();
	    break;

	case Ph_WM_FOCUS:
	    /* Just in case it's hidden and needs to be shown */
	    gui_mch_mousehide(MOUSE_SHOW);

	    if (we->event_state == Ph_WM_EVSTATE_FOCUS)
	    {
		gui_focus_change(TRUE);
		gui_mch_start_blink();
	    }
	    else
	    {
		gui_focus_change(FALSE);
		gui_mch_stop_blink();
	    }
	    break;

	case Ph_WM_RESIZE:
	    PtGetResource(gui.vimWindow, Pt_ARG_WIDTH, &width, 0);
	    PtGetResource(gui.vimWindow, Pt_ARG_HEIGHT, &height, 0);
#ifdef USE_PANEL_GROUP
	    width  -= (pg_margin_left + pg_margin_right);
	    height -= (pg_margin_top + pg_margin_bottom);
#endif
	    gui_resize_shell(*width, *height);
	    gui_set_shellsize(FALSE, FALSE, RESIZE_BOTH);
	    is_ignore_draw = FALSE;
	    PtEndFlux(gui.vimContainer);
	    PtContainerRelease(gui.vimContainer);
	    break;

	default:
	    break;
    }

    return Pt_CONTINUE;
}