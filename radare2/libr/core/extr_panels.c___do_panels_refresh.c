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
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {int isResizing; } ;
struct TYPE_5__ {TYPE_3__* panels; } ;
typedef  TYPE_1__ RCore ;

/* Variables and functions */
 int /*<<< orphan*/  __panel_all_clear (TYPE_3__*) ; 
 int /*<<< orphan*/  __panels_layout_refresh (TYPE_1__*) ; 

void __do_panels_refresh(RCore *core) {
	if (!core->panels) {
		return;
	}
	core->panels->isResizing = true;
	__panel_all_clear (core->panels);
	__panels_layout_refresh (core);
}