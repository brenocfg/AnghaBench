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
struct TYPE_3__ {int size; int perm; int /*<<< orphan*/  addr; int /*<<< orphan*/  hw; } ;
typedef  TYPE_1__ RBreakpointItem ;
typedef  int /*<<< orphan*/  RBreakpoint ;

/* Variables and functions */
#define  R_BP_PROT_EXEC 131 
#define  R_PERM_ACCESS 130 
#define  R_PERM_R 129 
#define  R_PERM_W 128 
 int /*<<< orphan*/  desc ; 
 int gdbr_remove_bp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gdbr_remove_hwa (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int gdbr_remove_hwbp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gdbr_remove_hwr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  gdbr_remove_hww (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int gdbr_set_bp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  gdbr_set_hwa (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int gdbr_set_hwbp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  gdbr_set_hwr (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  gdbr_set_hww (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int r_debug_gdb_breakpoint (RBreakpoint *bp, RBreakpointItem *b, bool set) {
	int ret = 0, bpsize;
	if (!b) {
		return false;
	}
	bpsize = b->size;
        // TODO handle conditions
	switch (b->perm) {
	case R_BP_PROT_EXEC : {
		if (set) {
			ret = b->hw?
					gdbr_set_hwbp (desc, b->addr, "", bpsize):
					gdbr_set_bp (desc, b->addr, "", bpsize);
		} else {
			ret = b->hw ? gdbr_remove_hwbp (desc, b->addr, bpsize) : gdbr_remove_bp (desc, b->addr, bpsize);
		}
		break;
	}
	// TODO handle size (area of watch in upper layer and then bpsize. For the moment watches are set on exact on byte
	case R_PERM_W: {
		if (set) {
			gdbr_set_hww (desc, b->addr, "", 1);
		} else {
			gdbr_remove_hww (desc, b->addr, 1);
		}
		break;
	}
	case R_PERM_R: {
		if (set) {
			gdbr_set_hwr (desc, b->addr, "", 1);
		} else {
			gdbr_remove_hwr (desc, b->addr, 1);
		}
		break;
	}
	case R_PERM_ACCESS: {
		if (set) {
			gdbr_set_hwa (desc, b->addr, "", 1);
		} else {
			gdbr_remove_hwa (desc, b->addr, 1);
		}
		break;
	}
	}
	return !ret;
}