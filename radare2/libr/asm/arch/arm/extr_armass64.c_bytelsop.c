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
struct TYPE_4__ {int reg_type; int type; int reg; int immediate; } ;
typedef  TYPE_2__ ArmOp ;

/* Variables and functions */
 int ARM_GPR ; 
 int ARM_REG32 ; 
 int ARM_REG64 ; 
 int UT32_MAX ; 
 scalar_t__ countTrailingZeros (int) ; 

__attribute__((used)) static ut32 bytelsop(ArmOp *op, int k) {
	ut32 data = UT32_MAX;

	if (op->operands[0].reg_type & ARM_REG64) {
		return data;
	}
	if (op->operands[1].reg_type & ARM_REG32) {
		return data;
	}
	if (op->operands[2].type & ARM_GPR) {
		if ((k & 0xf) != 8) {
			k--;
		}
		k += 0x00682000;
		data = k | op->operands[0].reg << 24 | op->operands[1].reg << 29 | (op->operands[1].reg & 56) << 13;
		data |= op->operands[2].reg << 8;
		return data;
	}

	int n = op->operands[2].immediate;
	if (n > 0xfff || n < -0x100) {
		return UT32_MAX;
	}
	// Half ops
	int halfop = false;
	if ((k & 0xf) == 8) {
		halfop = true;
		if (n == 0 || (countTrailingZeros(n) && n > 0)) {
			k++;
		}
	} else {
		if (n < 0) {
			k--;
		}
	}

	data = k | op->operands[0].reg << 24 | op->operands[1].reg << 29 | (op->operands[1].reg & 56) << 13;

	int imm = n;
	int low_shift = 20;
	int high_shift = 8;
	int top_shift = 10;
	if (n < 0) {
		imm = 0xfff + (n + 1);
	}
	if (halfop) {
		if (imm & 0x1 || n < 0) {
			data |= (0xf & imm) << low_shift ;
			data |= (0x7 & (imm >> 4)) << high_shift;
			data |= (0x7 & (imm >> 6)) << top_shift;
		} else {
			data |= (0xf & imm) << (low_shift - 3);
			data |= (0x7 & (imm >> 4)) << (high_shift + 13);
			data |= (0x7 & (imm >> 7)) << (top_shift  - 2);
		}
	} else {
		if (n < 0) {
			data |= (0xf & imm) << 20;
			data |= (0x1f & (imm >> 4)) << 8;
		} else {
			data |= (0xf & imm) << 18;
			data |= (0x3 & (imm >> 4)) << 22;
			data |= (0x7 & (imm >> 6)) << 8;
		}
	}
	return data;
}