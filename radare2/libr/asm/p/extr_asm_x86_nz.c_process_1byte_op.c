#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int ut8 ;
typedef  int st32 ;
struct TYPE_9__ {TYPE_1__* operands; } ;
struct TYPE_8__ {int bits; } ;
struct TYPE_7__ {int reg; int type; int immediate; int sign; int* regs; int offset; int offset_sign; int* scale; scalar_t__ extended; int /*<<< orphan*/  is_good_flag; } ;
typedef  TYPE_2__ RAsm ;
typedef  TYPE_3__ Opcode ;

/* Variables and functions */
 int OT_BYTE ; 
 int OT_CONSTANT ; 
 int OT_DWORD ; 
 int OT_MEMORY ; 
 int OT_QWORD ; 
 int OT_REGALL ; 
 int ST8_MAX ; 
 int ST8_MIN ; 
 int X86R_AL ; 
 int X86R_EBP ; 
 int X86R_ESP ; 
 int X86R_UNDEFINED ; 
 int /*<<< orphan*/  eprintf (char*) ; 
 int getsib (int) ; 
 int /*<<< orphan*/  is_valid_registers (TYPE_3__ const*) ; 

__attribute__((used)) static int process_1byte_op(RAsm *a, ut8 *data, const Opcode *op, int op1) {
	is_valid_registers (op);
	int l = 0;
	int mod_byte = 0;
	int reg = 0;
	int rm = 0;
	int rex = 0;
	int mem_ref = 0;
	st32 offset = 0;
	int ebp_reg = 0;

	if (!op->operands[1].is_good_flag) {
		return -1;
	}

	if (op->operands[0].reg == X86R_AL && op->operands[1].type & OT_CONSTANT) {
		data[l++] = op1 + 4;
		data[l++] = op->operands[1].immediate * op->operands[1].sign;
		return l;
	}

	if (a->bits == 64) {
		if (!(op->operands[0].type & op->operands[1].type)) {
			return -1;
		}
	}

	if (a->bits == 64 && ((op->operands[0].type & OT_QWORD) | (op->operands[1].type & OT_QWORD))) {
		if (op->operands[0].extended) {
				rex = 1;
		}
		if (op->operands[1].extended) {
			rex += 4;
		}
		data[l++] = 0x48 | rex;
	}

	if (op->operands[0].type & OT_MEMORY && op->operands[1].type & OT_REGALL) {
		if (a->bits == 64 && (op->operands[0].type & OT_DWORD) &&
		    (op->operands[1].type & OT_DWORD)) {
			data[l++] = 0x67;
		}
		if (op->operands[0].type & OT_BYTE && op->operands[1].type & OT_BYTE) {
			data[l++] = op1;
		} else if (op->operands[0].type & (OT_DWORD | OT_QWORD) &&
			   op->operands[1].type & (OT_DWORD | OT_QWORD)) {
			data[l++] = op1 + 0x1;
		} else {
			eprintf ("Error: mismatched operand sizes\n");
			return -1;
		}
		reg = op->operands[1].reg;
		rm = op->operands[0].regs[0];
		offset = op->operands[0].offset * op->operands[0].offset_sign;
		if (rm == -1) {
			rm = 5;
			mem_ref = 1;
		} else {
			if (offset) {
				mod_byte = 1;
				if (offset < ST8_MIN || offset > ST8_MAX) {
					mod_byte = 2;
				}
			} else if (op->operands[0].regs[1] != X86R_UNDEFINED) {
				rm = 4;
				offset = op->operands[0].regs[1] << 3;
			}
		}
	} else if (op->operands[0].type & OT_REGALL) {
		if (op->operands[1].type & OT_MEMORY) {
			if (op->operands[0].type & OT_BYTE && op->operands[1].type & OT_BYTE) {
				data[l++] = op1 + 0x2;
			} else if (op->operands[0].type & (OT_DWORD | OT_QWORD) &&
					   op->operands[1].type & (OT_DWORD | OT_QWORD)) {
				data[l++] = op1 + 0x3;
			} else {
				eprintf ("Error: mismatched operand sizes\n");
				return -1;
			}
			reg = op->operands[0].reg;
			rm = op->operands[1].regs[0];

			if (op->operands[1].scale[0] > 1) {
				if (op->operands[1].regs[1] != X86R_UNDEFINED) {
					data[l++] = op->operands[0].reg << 3 | 4;
					data[l++] = getsib (op->operands[1].scale[0]) << 6 |
										op->operands[1].regs[0] << 3 |
										op->operands[1].regs[1];
					return l;
				}
				data[l++] = op->operands[0].reg << 3 | 4; // 4 = SIB
				data[l++] = getsib (op->operands[1].scale[0]) << 6 | op->operands[1].regs[0] << 3 | 5;
				data[l++] = op->operands[1].offset * op->operands[1].offset_sign;
				data[l++] = 0;
				data[l++] = 0;
				data[l++] = 0;
				return l;
			}
			offset = op->operands[1].offset * op->operands[1].offset_sign;
			if (offset) {
				mod_byte = 1;
				if (offset < ST8_MIN || offset > ST8_MAX) {
					mod_byte = 2;
				}
			}

		} else if (op->operands[1].type & OT_REGALL) {
			if (op->operands[0].type & OT_BYTE && op->operands[1].type & OT_BYTE) {
				data[l++] = op1;
			} else if (op->operands[0].type & OT_DWORD && op->operands[1].type & OT_DWORD) {
				data[l++] = op1 + 0x1;
			}
			if (a->bits == 64) {
				if (op->operands[0].type & OT_QWORD &&
					op->operands[1].type & OT_QWORD) {
					data[l++] = op1 + 0x1;
				}
			}

			mod_byte = 3;
			reg = op->operands[1].reg;
			rm = op->operands[0].reg;
		}
	}
	if (op->operands[0].regs[0] == X86R_EBP ||
	    op->operands[1].regs[0] == X86R_EBP) {
			//reg += 8;
			ebp_reg = 1;
	}
	data[l++] = mod_byte << 6 | reg << 3 | rm;

	if (op->operands[0].regs[0] == X86R_ESP ||
	    op->operands[1].regs[0] == X86R_ESP) {
			data[l++] = 0x24;
	}
	if (offset || mem_ref || ebp_reg) {
	//if ((mod_byte > 0 && mod_byte < 3) || mem_ref) {
		data[l++] = offset;
		if (mod_byte == 2 || mem_ref) {
			data[l++] = offset >> 8;
			data[l++] = offset >> 16;
			data[l++] = offset >> 24;
		}
	}
	return l;
}