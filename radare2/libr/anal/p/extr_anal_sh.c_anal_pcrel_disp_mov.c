#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int ut8 ;
struct TYPE_7__ {int addr; } ;
struct TYPE_6__ {int base; int delta; } ;
typedef  TYPE_1__ RAnalValue ;
typedef  TYPE_2__ RAnalOp ;
typedef  int /*<<< orphan*/  RAnal ;

/* Variables and functions */
 TYPE_1__* r_anal_value_new () ; 

__attribute__((used)) static RAnalValue *anal_pcrel_disp_mov(RAnal* anal, RAnalOp* op, ut8 disp, int size) {
	RAnalValue *ret = r_anal_value_new ();
	if (size==2) {
		ret->base = op->addr + 4;
		ret->delta = disp << 1;
	} else {
		ret->base = (op->addr + 4) & ~0x03;
		ret->delta = disp << 2;
	}

	return ret;
}