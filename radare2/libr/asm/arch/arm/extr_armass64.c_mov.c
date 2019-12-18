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
struct TYPE_5__ {TYPE_1__* operands; int /*<<< orphan*/  mnemonic; } ;
struct TYPE_4__ {int reg_type; int type; int reg; int immediate; } ;
typedef  TYPE_2__ ArmOp ;

/* Variables and functions */
 int ARM_CONSTANT ; 
 int ARM_GPR ; 
 int ARM_REG32 ; 
 int ARM_REG64 ; 
 int UT32_MAX ; 
 int /*<<< orphan*/  strncmp (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static ut32 mov(ArmOp *op) {
	int k = 0;
	ut32 data = UT32_MAX;
	if (!strncmp (op->mnemonic, "movz", 4)) {
		if (op->operands[0].reg_type & ARM_REG64) {
			k = 0x80d2;
		} else if (op->operands[0].reg_type & ARM_REG32) {
			k = 0x8052;
		}
	} else if (!strncmp (op->mnemonic, "movk", 4)) {
		if (op->operands[0].reg_type & ARM_REG32) {
			k = 0x8072;
		} else if (op->operands[0].reg_type & ARM_REG64) {
			k = 0x80f2;
		}
	} else if (!strncmp (op->mnemonic, "movn", 4)) {
		if (op->operands[0].reg_type & ARM_REG32) {
			k = 0x8012;
		} else if (op->operands[0].reg_type & ARM_REG64) {
			k = 0x8092;
		}
	} else if (!strncmp (op->mnemonic, "mov", 3)) {
		//printf ("%d - %d [%d]\n", op->operands[0].type, op->operands[1].type, ARM_GPR);
		if (op->operands[0].type & ARM_GPR) {
			if (op->operands[1].type & ARM_GPR) {
				if (op->operands[1].reg_type & ARM_REG64) {
					k = 0xe00300aa;
				} else {
					k = 0xe003002a;
				}
				data = k | op->operands[1].reg << 8;
			} else if (op->operands[1].type & ARM_CONSTANT) {
				k = 0x80d2;
				data = k | op->operands[1].immediate << 29;
			}
			data |=  op->operands[0].reg << 24;
		}
		return data;
	}

	data = k;
	data |= (op->operands[0].reg << 24); // arg(0)
	data |= ((op->operands[1].immediate & 7) << 29); // arg(1)
	data |= (((op->operands[1].immediate >> 3) & 0xff) << 16); // arg(1)
	data |= ((op->operands[1].immediate >> 10) << 7); // arg(1)
	return data;
}