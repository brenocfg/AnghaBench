#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int ut32 ;
struct TYPE_5__ {int operands_count; TYPE_1__* operands; } ;
struct TYPE_4__ {int type; int reg; int reg_type; } ;
typedef  TYPE_2__ ArmOp ;

/* Variables and functions */
 int ARM_GPR ; 
 int ARM_REG64 ; 
 int UT32_MAX ; 

__attribute__((used)) static ut32 arithmetic (ArmOp *op, int k) {
	ut32 data = UT32_MAX;
	if (op->operands_count < 3) {
		return data;
	}

	if (!(op->operands[0].type & ARM_GPR &&
	      op->operands[1].type & ARM_GPR)) {
		return data;
	}
	if (op->operands[2].type & ARM_GPR) {
		k -= 6;
	}

	data = k;
	data += op->operands[0].reg << 24;
	data += (op->operands[1].reg & 7) << (24 + 5);
	data += (op->operands[1].reg >> 3) << 16;
	if (op->operands[2].reg_type & ARM_REG64) {
		data += op->operands[2].reg << 8;
	} else {
		data += (op->operands[2].reg & 0x3f) << 18;
		data += (op->operands[2].reg >> 6) << 8;
	}
	return data;
}