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
struct unwind_info {int /*<<< orphan*/  max_stack; } ;
typedef  int /*<<< orphan*/  Dwfl_Frame ;
typedef  int /*<<< orphan*/  Dwarf_Addr ;

/* Variables and functions */
 int DWARF_CB_ABORT ; 
 int DWARF_CB_OK ; 
 int /*<<< orphan*/  dwfl_errmsg (int) ; 
 int /*<<< orphan*/  dwfl_frame_pc (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int*) ; 
 scalar_t__ entry (int /*<<< orphan*/ ,struct unwind_info*) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  report_module (int /*<<< orphan*/ ,struct unwind_info*) ; 

__attribute__((used)) static int
frame_callback(Dwfl_Frame *state, void *arg)
{
	struct unwind_info *ui = arg;
	Dwarf_Addr pc;
	bool isactivation;

	if (!dwfl_frame_pc(state, &pc, NULL)) {
		pr_err("%s", dwfl_errmsg(-1));
		return DWARF_CB_ABORT;
	}

	// report the module before we query for isactivation
	report_module(pc, ui);

	if (!dwfl_frame_pc(state, &pc, &isactivation)) {
		pr_err("%s", dwfl_errmsg(-1));
		return DWARF_CB_ABORT;
	}

	if (!isactivation)
		--pc;

	return entry(pc, ui) || !(--ui->max_stack) ?
	       DWARF_CB_ABORT : DWARF_CB_OK;
}