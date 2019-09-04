#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  st64 ;
struct TYPE_8__ {int /*<<< orphan*/  reg; } ;
struct TYPE_7__ {int /*<<< orphan*/  memref; int /*<<< orphan*/  regdelta; } ;
typedef  TYPE_1__ RAnalValue ;
typedef  TYPE_2__ RAnal ;

/* Variables and functions */
 int /*<<< orphan*/  R_REG_TYPE_GPR ; 
 TYPE_1__* anal_fill_ai_rg (TYPE_2__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  r_reg_get (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * regs ; 

__attribute__((used)) static RAnalValue *anal_fill_r0_reg_ref(RAnal *anal, int reg, st64 size) {
	RAnalValue *ret = anal_fill_ai_rg (anal, 0);
	ret->regdelta = r_reg_get (anal->reg, regs[reg], R_REG_TYPE_GPR);
	ret->memref = size;
	return ret;
}