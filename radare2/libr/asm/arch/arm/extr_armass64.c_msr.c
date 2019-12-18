#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int ut32 ;
struct TYPE_7__ {scalar_t__ val; scalar_t__ name; } ;
struct TYPE_6__ {TYPE_1__* operands; } ;
struct TYPE_5__ {int reg_type; scalar_t__ type; scalar_t__ immediate; scalar_t__ sp_val; scalar_t__ reg; } ;
typedef  TYPE_2__ ArmOp ;

/* Variables and functions */
 scalar_t__ ARM_CONSTANT ; 
 int ARM_REG64 ; 
 int ARM_SP ; 
 int UT32_MAX ; 
 TYPE_3__* msr_const ; 

__attribute__((used)) static ut32 msr(ArmOp *op, int w) {
	ut32 data = UT32_MAX;
	ut32 seq_data = UT32_MAX;
	int is_immediate = 0;
	int i;
	ut32 r, b;
	/* handle swapped args */
	if (w) {
		if (op->operands[1].reg_type != (ARM_REG64 | ARM_SP)) {
			if (op->operands[1].type == ARM_CONSTANT) {
				for (i = 0; msr_const[i].name; i++) {
					if (op->operands[1].immediate == msr_const[i].val) {
						op->operands[1].sp_val = msr_const[i].val;
						op->operands[1].reg = op->operands[1].immediate;
						break;
					}
				}
			} else {
				return data;
			}
		}
		r = op->operands[0].reg;
		b = op->operands[1].sp_val;
	} else {
		if (op->operands[0].reg_type != (ARM_REG64 | ARM_SP)) {
			if (op->operands[0].type == ARM_CONSTANT) {
				for (i = 0; msr_const[i].name; i++) {
					if (op->operands[0].immediate == msr_const[i].val) {
						op->operands[0].sp_val = msr_const[i].val;
						op->operands[0].reg = op->operands[0].immediate;
						break;
					}
				}
			} else {
				return data;
			}
		}
		r = op->operands[1].reg;
		if ( op->operands[1].sp_val == 0xfffe ) {
			is_immediate = 1;
			r = op->operands[1].immediate;
		}
		b = op->operands[0].sp_val;
	}
	data = 0x00000000;

	if (is_immediate) {
		//only msr has immediate mode
		data = 0xd500401f;
		if (b == 0xc210) { //op0 is SPSel
			b = 0x05; //set to immediate mode encoding
		}

		data |= (b & 0xf0) << 12; //op1
		data |= (b & 0x0f) << 5; //op2
		data |= (r & 0xf) << 8; //CRm(#imm)

	} else {
		if (w) {
			/* mrs */
			data |= 0xd5200000;
		} else {
			data |= 0xd5000000;
		}
		data |= b << 5;
		data |= r;
	}
	seq_data = 0x00000000;
	seq_data |= (data & 0xff) << 8*3;
	seq_data |= (data & 0xff00) << 8*1;
	seq_data |= (data & 0xff0000) >> 8*1;
	seq_data |= (data & 0xff000000) >> 8*3;
/*
if (op->operands[1].reg_type == ARM_REG64) {
		data |= op->operands[1].reg << 24;
	}
*/
	return seq_data;
}