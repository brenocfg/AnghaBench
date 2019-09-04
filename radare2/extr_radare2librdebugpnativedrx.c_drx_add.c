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
struct TYPE_6__ {int nhwbps; } ;
struct TYPE_5__ {int /*<<< orphan*/  perm; int /*<<< orphan*/  size; int /*<<< orphan*/  addr; } ;
typedef  int /*<<< orphan*/  RDebug ;
typedef  TYPE_1__ RBreakpointItem ;
typedef  TYPE_2__ RBreakpoint ;

/* Variables and functions */
 int /*<<< orphan*/  R_REG_TYPE_DRX ; 
 int /*<<< orphan*/  r_debug_drx_set (int /*<<< orphan*/ *,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_debug_reg_sync (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

bool drx_add(RDebug *dbg, RBreakpoint *bp, RBreakpointItem *b) {
	if (bp->nhwbps < 4) {
		r_debug_reg_sync (dbg, R_REG_TYPE_DRX, false);
		r_debug_drx_set (dbg, bp->nhwbps, b->addr, b->size, b->perm, 0);
		r_debug_reg_sync (dbg, R_REG_TYPE_DRX, true);
		bp->nhwbps++;
		return true;
	}
	return false;
}