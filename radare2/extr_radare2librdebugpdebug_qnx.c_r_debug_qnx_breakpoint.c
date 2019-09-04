#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  addr; scalar_t__ hw; } ;
typedef  TYPE_1__ RBreakpointItem ;
typedef  int /*<<< orphan*/  RBreakpoint ;

/* Variables and functions */
 int /*<<< orphan*/  desc ; 
 int qnxr_remove_bp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int qnxr_remove_hwbp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int qnxr_set_bp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 int qnxr_set_hwbp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int r_debug_qnx_breakpoint (RBreakpoint *bp, RBreakpointItem *b, bool set) {
	if (!b) {
		return false;
	}
	int ret = set
		? b->hw
			? qnxr_set_hwbp (desc, b->addr, "")
			: qnxr_set_bp (desc, b->addr, "")
		: b->hw
			? qnxr_remove_hwbp (desc, b->addr)
			: qnxr_remove_bp (desc, b->addr);
	return !ret;
}