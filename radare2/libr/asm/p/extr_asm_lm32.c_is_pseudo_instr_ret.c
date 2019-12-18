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
struct TYPE_3__ {scalar_t__ op; int src0_reg; } ;
typedef  TYPE_1__ RAsmLm32Instruction ;

/* Variables and functions */
 scalar_t__ lm32_op_b ; 

__attribute__((used)) static bool is_pseudo_instr_ret(RAsmLm32Instruction *instr) {
	//"ra" == 0x1d
	return (instr->op == lm32_op_b) && (instr->src0_reg == 0x1d);
}