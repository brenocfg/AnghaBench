#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ ut64 ;
struct TYPE_8__ {scalar_t__ offset; } ;
typedef  int /*<<< orphan*/  RPanel ;
typedef  TYPE_1__ RCore ;

/* Variables and functions */
 int /*<<< orphan*/  PANEL_CMD_DISASSEMBLY ; 
 scalar_t__ UT64_MAX ; 
 scalar_t__ __check_panel_type (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __set_addr_by_type (TYPE_1__*,int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  __set_panel_addr (TYPE_1__*,int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  __set_refresh_all (TYPE_1__*,int,int) ; 
 int __show_status (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  r_core_visual_refs (TYPE_1__*,int,int) ; 

void __handle_refs(RCore *core, RPanel *panel, ut64 tmp) {
	if (tmp != UT64_MAX) {
		core->offset = tmp;
	}
	int key = __show_status(core, "xrefs:x refs:X ");
	switch (key) {
	case 'x':
		(void)r_core_visual_refs(core, true, false);
		break;
	case 'X':
		(void)r_core_visual_refs(core, false, false);
		break;
	default:
		break;
	}
	if (__check_panel_type (panel, PANEL_CMD_DISASSEMBLY)) {
		__set_panel_addr (core, panel, core->offset);
		__set_refresh_all (core, false, false);
		return;
	}
	__set_addr_by_type (core, PANEL_CMD_DISASSEMBLY, core->offset);
}