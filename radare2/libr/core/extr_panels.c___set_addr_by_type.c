#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ut64 ;
struct TYPE_7__ {TYPE_1__* panels; } ;
struct TYPE_6__ {int n_panels; } ;
typedef  TYPE_1__ RPanels ;
typedef  int /*<<< orphan*/  RPanel ;
typedef  TYPE_2__ RCore ;

/* Variables and functions */
 int /*<<< orphan*/  __check_panel_type (int /*<<< orphan*/ *,char const*) ; 
 int /*<<< orphan*/ * __get_panel (TYPE_1__*,int) ; 
 int /*<<< orphan*/  __set_panel_addr (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void __set_addr_by_type(RCore *core, const char *cmd, ut64 addr) {
	RPanels *panels = core->panels;
	int i;
	for (i = 0; i < panels->n_panels; i++) {
		RPanel *p = __get_panel (panels, i);
		if (!__check_panel_type (p, cmd)) {
			continue;
		}
		__set_panel_addr (core, p, addr);
	}
}