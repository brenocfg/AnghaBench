#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int ut8 ;
typedef  int st32 ;
struct TYPE_6__ {TYPE_1__* operands; } ;
struct TYPE_5__ {int type; int* regs; int offset; int offset_sign; int reg; } ;
typedef  int /*<<< orphan*/  RAsm ;
typedef  TYPE_2__ Opcode ;

/* Variables and functions */
 int OT_GPREG ; 
 int OT_MEMORY ; 
 int ST8_MAX ; 
 int ST8_MIN ; 
 int X86R_EAX ; 
 int /*<<< orphan*/  is_valid_registers (TYPE_2__ const*) ; 

__attribute__((used)) static int opxchg(RAsm *a, ut8 *data, const Opcode *op) {
	is_valid_registers (op);
	int l = 0;
	int mod_byte = 0;
	int reg = 0;
	int rm = 0;
	st32 offset = 0;

	if (op->operands[0].type & OT_MEMORY || op->operands[1].type & OT_MEMORY) {
		data[l++] = 0x87;
		if (op->operands[0].type & OT_MEMORY) {
			rm = op->operands[0].regs[0];
			offset = op->operands[0].offset * op->operands[0].offset_sign;
			reg = op->operands[1].reg;
		} else if (op->operands[1].type & OT_MEMORY) {
			rm = op->operands[1].regs[0];
			offset = op->operands[1].offset * op->operands[1].offset_sign;
			reg = op->operands[0].reg;
		}
		if (offset) {
			mod_byte = 1;
			if (offset < ST8_MIN || offset > ST8_MAX) {
				mod_byte = 2;
			}
		}
	} else {
		if (op->operands[0].reg == X86R_EAX &&
			op->operands[1].type & OT_GPREG) {
			data[l++] = 0x90 + op->operands[1].reg;
			return l;
		} else if (op->operands[1].reg == X86R_EAX &&
				   op->operands[0].type & OT_GPREG) {
			data[l++] = 0x90 + op->operands[0].reg;
			return l;
		} else if (op->operands[0].type & OT_GPREG &&
				   op->operands[1].type & OT_GPREG) {
			mod_byte = 3;
			data[l++] = 0x87;
			reg = op->operands[1].reg;
			rm = op->operands[0].reg;
		}
	}
	data[l++] = mod_byte << 6 | reg << 3 | rm;
	if (mod_byte > 0 && mod_byte < 3) {
		data[l++] = offset;
		if (mod_byte == 2) {
			data[l++] = offset >> 8;
			data[l++] = offset >> 16;
			data[l++] = offset >> 24;
		}
	}
	return l;
}