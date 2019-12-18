#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  RPanel ;

/* Variables and functions */
 int /*<<< orphan*/  PANEL_CMD_DISASSEMBLY ; 
 int /*<<< orphan*/  PANEL_CMD_HEXDUMP ; 
 int /*<<< orphan*/  PANEL_CMD_REGISTERS ; 
 int /*<<< orphan*/  PANEL_CMD_STACK ; 
 scalar_t__ __check_panel_type (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

bool __is_normal_cursor_type(RPanel *panel) {
	return (__check_panel_type (panel, PANEL_CMD_STACK) ||
			__check_panel_type (panel, PANEL_CMD_REGISTERS) ||
			__check_panel_type (panel, PANEL_CMD_DISASSEMBLY) ||
			__check_panel_type (panel, PANEL_CMD_HEXDUMP));
}