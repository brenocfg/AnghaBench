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
struct TYPE_2__ {int /*<<< orphan*/  vimTextArea; } ;
typedef  int /*<<< orphan*/  PtWidget_t ;
typedef  int /*<<< orphan*/  PtCallbackInfo_t ;

/* Variables and functions */
 int /*<<< orphan*/  PtGiveFocus (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int Pt_CONTINUE ; 
 TYPE_1__ gui ; 

__attribute__((used)) static int
gui_ph_handle_menu_unrealized(
	PtWidget_t *widget,
	void *data,
	PtCallbackInfo_t *info)
{
    PtGiveFocus(gui.vimTextArea, NULL);
    return Pt_CONTINUE;
}