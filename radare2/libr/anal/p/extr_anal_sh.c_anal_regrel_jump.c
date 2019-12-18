#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  size_t ut8 ;
struct TYPE_10__ {int /*<<< orphan*/  reg; } ;
struct TYPE_9__ {scalar_t__ addr; } ;
struct TYPE_8__ {scalar_t__ base; int /*<<< orphan*/  reg; } ;
typedef  TYPE_1__ RAnalValue ;
typedef  TYPE_2__ RAnalOp ;
typedef  TYPE_3__ RAnal ;

/* Variables and functions */
 int /*<<< orphan*/  R_REG_TYPE_GPR ; 
 TYPE_1__* r_anal_value_new () ; 
 int /*<<< orphan*/  r_reg_get (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * regs ; 

__attribute__((used)) static RAnalValue *anal_regrel_jump(RAnal* anal, RAnalOp* op, ut8 reg) {
	RAnalValue *ret = r_anal_value_new ();
	ret->reg = r_reg_get (anal->reg, regs[reg], R_REG_TYPE_GPR);
	ret->base = op->addr + 4;
	return ret;
}