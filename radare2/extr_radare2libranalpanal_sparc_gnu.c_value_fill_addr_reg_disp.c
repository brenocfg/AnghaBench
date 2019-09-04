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
typedef  int /*<<< orphan*/  st64 ;
struct TYPE_7__ {int /*<<< orphan*/  reg; } ;
struct TYPE_6__ {int /*<<< orphan*/  delta; int /*<<< orphan*/  reg; } ;
typedef  TYPE_1__ RAnalValue ;
typedef  TYPE_2__ RAnal ;

/* Variables and functions */
 int /*<<< orphan*/  R_REG_TYPE_GPR ; 
 int /*<<< orphan*/ * gpr_regs ; 
 TYPE_1__* r_anal_value_new () ; 
 int /*<<< orphan*/  r_reg_get (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static RAnalValue * value_fill_addr_reg_disp(RAnal const * const anal, const int ireg, const st64 disp) {
	RAnalValue *val = r_anal_value_new();
	val->reg = r_reg_get(anal->reg, gpr_regs[ireg], R_REG_TYPE_GPR);
	val->delta = disp;
	return val;
}