#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int /*<<< orphan*/  vimContainer; int /*<<< orphan*/  vimWindow; } ;
struct TYPE_5__ {int /*<<< orphan*/  pos; } ;
typedef  TYPE_1__ PhArea_t ;

/* Variables and functions */
 int /*<<< orphan*/  PtSetResource (int /*<<< orphan*/ ,int /*<<< orphan*/ ,TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  PtWidgetArea (int /*<<< orphan*/ ,TYPE_1__*) ; 
 int /*<<< orphan*/  PtWidgetPos (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Pt_ARG_AREA ; 
 TYPE_2__ gui ; 

__attribute__((used)) static void
gui_ph_resize_container(void)
{
    PhArea_t area;

    PtWidgetArea(gui.vimWindow, &area);
    PtWidgetPos (gui.vimContainer, &area.pos);

    PtSetResource(gui.vimContainer, Pt_ARG_AREA, &area, 0);
}