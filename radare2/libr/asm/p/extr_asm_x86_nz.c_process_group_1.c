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
struct TYPE_9__ {TYPE_1__* operands; int /*<<< orphan*/  mnemonic; } ;
struct TYPE_8__ {int bits; } ;
struct TYPE_7__ {int type; int immediate; int sign; int reg; int offset; int offset_sign; int* regs; int /*<<< orphan*/  is_good_flag; } ;
typedef  TYPE_2__ RAsm ;
typedef  TYPE_3__ Opcode ;

/* Variables and functions */
 int OT_BYTE ; 
 int OT_DWORD ; 
 int OT_MEMORY ; 
 int OT_QWORD ; 
 int ST8_MAX ; 
 int ST8_MIN ; 
 int X86R_EAX ; 
 int X86R_EBP ; 
 int X86R_ESP ; 
 int /*<<< orphan*/  eprintf (char*) ; 
 int /*<<< orphan*/  is_valid_registers (TYPE_3__ const*) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int process_group_1(RAsm *a, ut8 *data, const Opcode *op) {
	is_valid_registers (op);
	int l = 0;
	int modrm = 0;
	int mod_byte = 0;
	int offset = 0;
	int mem_ref = 0;
	st32 immediate = 0;

	if (!op->operands[1].is_good_flag) {
		return -1;
	}
	if (a->bits == 64 && op->operands[0].type & OT_QWORD) {
		data[l++] = 0x48;
	}
	if (!strcmp (op->mnemonic, "adc")) {
		modrm = 2;
	} else if (!strcmp (op->mnemonic, "add")) {
		modrm = 0;
	} else if (!strcmp (op->mnemonic, "or")) {
		modrm = 1;
	} else if (!strcmp (op->mnemonic, "and")) {
		modrm = 4;
	} else if (!strcmp (op->mnemonic, "xor")) {
		modrm = 6;
	} else if (!strcmp (op->mnemonic, "sbb")) {
		modrm = 3;
	} else if (!strcmp (op->mnemonic, "sub")) {
		modrm = 5;
	} else if (!strcmp (op->mnemonic, "cmp")) {
		modrm = 7;
	}
	immediate = op->operands[1].immediate * op->operands[1].sign;

	if (op->operands[0].type & OT_DWORD ||
		op->operands[0].type & OT_QWORD) {
		if (op->operands[1].immediate < 128) {
			data[l++] = 0x83;
		} else if (op->operands[0].reg != X86R_EAX ||
		           op->operands[0].type & OT_MEMORY) {
			data[l++] = 0x81;
		}
	} else if (op->operands[0].type & OT_BYTE) {
		if (op->operands[1].immediate > 255) {
			eprintf ("Error: Immediate exceeds bounds\n");
			return -1;
		}
		data[l++] = 0x80;
	}
	if (op->operands[0].type & OT_MEMORY) {
		offset = op->operands[0].offset * op->operands[0].offset_sign;
		if (op->operands[0].offset || op->operands[0].regs[0] == X86R_EBP) {
			mod_byte = 1;
		}
		if (offset < ST8_MIN || offset > ST8_MAX) {
			mod_byte = 2;
		}
		int reg0 = op->operands[0].regs[0];
		if (reg0 == -1) {
			mem_ref = 1;
			reg0 = 5;
			mod_byte = 0;
		}
		data[l++] = mod_byte << 6 | modrm << 3 | reg0;
		if (op->operands[0].regs[0] == X86R_ESP) {
			data[l++] = 0x24;
		}
		if (mod_byte || mem_ref) {
			data[l++] = offset;
			if (mod_byte == 2 || mem_ref) {
				data[l++] = offset >> 8;
				data[l++] = offset >> 16;
				data[l++] = offset >> 24;
			}
		}
	} else {
		if (op->operands[1].immediate > 127 && op->operands[0].reg == X86R_EAX) {
			data[l++] = 5 | modrm << 3 | op->operands[0].reg;
		} else {
			mod_byte = 3;
			data[l++] = mod_byte << 6 | modrm << 3 | op->operands[0].reg;
		}

	}

	data[l++] = immediate;
	if ((immediate > 127 || immediate < -128) &&
	    ((op->operands[0].type & OT_DWORD) || (op->operands[0].type & OT_QWORD))) {
		data[l++] = immediate >> 8;
		data[l++] = immediate >> 16;
		data[l++] = immediate >> 24;
	}
	return l;
}