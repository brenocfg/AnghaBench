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
struct TYPE_9__ {TYPE_2__* operands; int /*<<< orphan*/  mnemonic; } ;
struct TYPE_8__ {int type; int immediate; int sign; int* regs; int offset; int offset_sign; int reg; } ;
struct TYPE_7__ {int bits; } ;
typedef  TYPE_1__ RAsm ;
typedef  TYPE_2__ Operand ;
typedef  TYPE_3__ Opcode ;

/* Variables and functions */
 int OT_BYTE ; 
 int OT_DWORD ; 
 int OT_GPREG ; 
 int OT_MEMORY ; 
 int OT_QWORD ; 
 int OT_WORD ; 
 int /*<<< orphan*/  eprintf (char*) ; 
 int /*<<< orphan*/  is_valid_registers (TYPE_3__ const*) ; 
 int /*<<< orphan*/  strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int process_group_2(RAsm *a, ut8 *data, const Opcode *op) {
	is_valid_registers (op);
	int l = 0;
	int modrm = 0;
	int mod_byte = 0;
	int reg0 = 0;

	if (a->bits == 64 && op->operands[0].type & OT_QWORD) { data[l++] = 0x48; }

	if (!strcmp (op->mnemonic, "rol")) {
		modrm = 0;
	} else if (!strcmp (op->mnemonic, "ror")) {
		modrm = 1;
	} else if (!strcmp (op->mnemonic, "rcl")) {
		modrm = 2;
	} else if (!strcmp (op->mnemonic, "rcr")) {
		modrm = 3;
	} else if (!strcmp (op->mnemonic, "shl")) {
		modrm = 4;
	} else if (!strcmp (op->mnemonic, "shr")) {
		modrm = 5;
	} else if (!strcmp (op->mnemonic, "sal")) {
		modrm = 6;
	} else if (!strcmp (op->mnemonic, "sar")) {
		modrm = 7;
	}

	st32 immediate = op->operands[1].immediate * op->operands[1].sign;
	if (immediate > 255 || immediate < -128) {
		eprintf ("Error: Immediate exceeds bounds\n");
		return -1;
	}

	if (op->operands[0].type & (OT_DWORD | OT_QWORD)) {
		if (op->operands[1].type & (OT_GPREG | OT_BYTE)) {
			data[l++] = 0xd3;
		} else if (immediate == 1) {
			data[l++] = 0xd1;
		} else {
			data[l++] = 0xc1;
		}
	} else if (op->operands[0].type & OT_BYTE) {
		const Operand *o = &op->operands[0];
		if (o->regs[0] != -1 && o->regs[1] != -1) {
			data[l++] = 0xc0;
			data[l++] = 0x44;
			data[l++] = o->regs[0]| (o->regs[1]<<3);
			data[l++] = (ut8)((o->offset*o->offset_sign) & 0xff);
			data[l++] = immediate;
			return l;
		} else if (op->operands[1].type & (OT_GPREG | OT_WORD)) {
			data[l++] = 0xd2;
		} else if (immediate == 1) {
			data[l++] = 0xd0;
		} else {
			data[l++] = 0xc0;
		}
	}
	if (op->operands[0].type & OT_MEMORY) {
		reg0 = op->operands[0].regs[0];
		mod_byte = 0;
	} else {
		reg0 = op->operands[0].reg;
		mod_byte = 3;
	}
	data[l++] = mod_byte << 6 | modrm << 3 | reg0;
	if (immediate != 1 && !(op->operands[1].type & OT_GPREG)) {
		data[l++] = immediate;
	}
	return l;
}