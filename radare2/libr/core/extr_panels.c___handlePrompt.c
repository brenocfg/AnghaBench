#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {int /*<<< orphan*/  offset; } ;
struct TYPE_9__ {int n_panels; } ;
typedef  TYPE_1__ RPanels ;
typedef  int /*<<< orphan*/  RPanel ;
typedef  TYPE_2__ RCore ;

/* Variables and functions */
 int /*<<< orphan*/  PANEL_CMD_DISASSEMBLY ; 
 scalar_t__ __check_panel_type (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * __get_panel (TYPE_1__*,int) ; 
 int /*<<< orphan*/  __set_panel_addr (TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __set_refresh_all (TYPE_2__*,int,int) ; 
 int /*<<< orphan*/  r_core_visual_prompt_input (TYPE_2__*) ; 

void __handlePrompt(RCore *core, RPanels *panels) {
	r_core_visual_prompt_input (core);
	int i;
	for (i = 0; i < panels->n_panels; i++) {
		RPanel *p = __get_panel (panels, i);
		if (__check_panel_type (p, PANEL_CMD_DISASSEMBLY)) {
			__set_panel_addr (core, p, core->offset);
			break;
		}
	}
	__set_refresh_all (core, false, false);
}