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
struct TYPE_5__ {int /*<<< orphan*/  vimTextArea; } ;
struct TYPE_4__ {scalar_t__ reason; } ;
typedef  int /*<<< orphan*/  PtWidget_t ;
typedef  TYPE_1__ PtCallbackInfo_t ;

/* Variables and functions */
 int /*<<< orphan*/  MOUSE_SHOW ; 
 int /*<<< orphan*/  Ph_EV_PTR_MOTION_NOBUTTON ; 
 int /*<<< orphan*/  PtAddEventHandler (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  PtRemoveEventHandler (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ Pt_CB_LOST_FOCUS ; 
 int Pt_CONTINUE ; 
 TYPE_3__ gui ; 
 int /*<<< orphan*/  gui_mch_mousehide (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gui_ph_handle_mouse ; 

__attribute__((used)) static int
gui_ph_handle_focus(PtWidget_t *widget, void *data, PtCallbackInfo_t *info)
{
    if (info->reason == Pt_CB_LOST_FOCUS)
    {
	PtRemoveEventHandler(gui.vimTextArea, Ph_EV_PTR_MOTION_NOBUTTON,
		gui_ph_handle_mouse, NULL);

	gui_mch_mousehide(MOUSE_SHOW);
    }
    else
    {
	PtAddEventHandler(gui.vimTextArea, Ph_EV_PTR_MOTION_NOBUTTON,
		gui_ph_handle_mouse, NULL);
    }
    return Pt_CONTINUE;
}