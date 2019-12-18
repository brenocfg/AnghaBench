#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  (* breakpoint ) (TYPE_1__*,int /*<<< orphan*/ *,int) ;} ;
typedef  int /*<<< orphan*/  RBreakpointItem ;
typedef  TYPE_1__ RBreakpoint ;

/* Variables and functions */
 int /*<<< orphan*/  stub1 (TYPE_1__*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void r_bp_watch_add_hw(RBreakpoint *bp, RBreakpointItem *b) {
	if (bp->breakpoint) {
		bp->breakpoint (bp, b, true);
	}
}