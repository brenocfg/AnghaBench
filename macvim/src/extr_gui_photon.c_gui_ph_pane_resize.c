#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  vimContainer; } ;
typedef  int /*<<< orphan*/  PtWidget_t ;
typedef  int /*<<< orphan*/  PtCallbackInfo_t ;

/* Variables and functions */
 int /*<<< orphan*/  PtContainerHold (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PtStartFlux (int /*<<< orphan*/ ) ; 
 scalar_t__ PtWidgetIsRealized (int /*<<< orphan*/ *) ; 
 int Pt_CONTINUE ; 
 int /*<<< orphan*/  TRUE ; 
 TYPE_1__ gui ; 
 int /*<<< orphan*/  is_ignore_draw ; 

__attribute__((used)) static int
gui_ph_pane_resize(PtWidget_t *widget, void *data, PtCallbackInfo_t *info)
{
    if (PtWidgetIsRealized(widget))
    {
	is_ignore_draw = TRUE;
	PtStartFlux(gui.vimContainer);
	PtContainerHold(gui.vimContainer);
    }

    return Pt_CONTINUE;
}