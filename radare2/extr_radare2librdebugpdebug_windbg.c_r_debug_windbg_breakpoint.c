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
struct TYPE_3__ {int /*<<< orphan*/  hw; int /*<<< orphan*/  addr; int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ RBreakpointItem ;
typedef  int /*<<< orphan*/  RBreakpoint ;

/* Variables and functions */
 int /*<<< orphan*/  wctx ; 
 int windbg_bkpt (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static int r_debug_windbg_breakpoint(RBreakpoint *bp, RBreakpointItem *b, bool set) {
	int *tag;
	if (!b) {
		return false;
	}
	// Use a 32 bit word here to keep this compatible with 32 bit hosts
	tag = (int *)&b->data;
	return windbg_bkpt (wctx, b->addr, set, b->hw, tag);
}