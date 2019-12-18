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
typedef  int /*<<< orphan*/  ut8 ;
struct TYPE_3__ {int /*<<< orphan*/  reg; } ;
typedef  TYPE_1__ RDebug ;

/* Variables and functions */
 int /*<<< orphan*/  r_reg_read_regs (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  wctx ; 
 int windbg_read_reg (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int r_debug_windbg_reg_read(RDebug *dbg, int type, ut8 *buf, int size) {
	int ret = windbg_read_reg(wctx, buf, size);
	if (!ret || size != ret) {
		return -1;
	}
	r_reg_read_regs (dbg->reg, buf, ret);
	// Report as if no register has been written as we've already updated the arena here
	return 0;
}