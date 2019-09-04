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
struct TYPE_5__ {TYPE_1__* operands; } ;
struct TYPE_4__ {int reg_type; int shift_amount; int reg; int shift; } ;
typedef  TYPE_2__ ArmOp ;

/* Variables and functions */
 int ARM_NO_SHIFT ; 
 int ARM_REG32 ; 
 int ARM_REG64 ; 
 int UT32_MAX ; 

__attribute__((used)) static ut32 cmp(ArmOp *op) {
	ut32 data = UT32_MAX;
	int k = 0;
	if (op->operands[0].reg_type & ARM_REG64 && op->operands[1].reg_type & ARM_REG64) {
		k =  0x1f0000eb;
	} else if (op->operands[0].reg_type & ARM_REG32 && op->operands[1].reg_type & ARM_REG32) {
		if (op->operands[2].shift_amount > 31) {
			return UT32_MAX;
		}
		k =  0x1f00006b;
	} else {
		return UT32_MAX;
	}

	data = k | (op->operands[0].reg & 0x18) << 13 | op->operands[0].reg << 29 | op->operands[1].reg << 8;

	if (op->operands[2].shift != ARM_NO_SHIFT) {
		data |= op->operands[2].shift_amount << 18 | op->operands[2].shift << 14;
	}
	return data;
}