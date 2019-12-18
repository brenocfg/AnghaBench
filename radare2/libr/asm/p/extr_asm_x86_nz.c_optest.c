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
struct TYPE_9__ {TYPE_1__* operands; } ;
struct TYPE_8__ {int bits; } ;
struct TYPE_7__ {int type; int reg_size; int reg; int immediate; int* regs; scalar_t__ extended; } ;
typedef  TYPE_2__ RAsm ;
typedef  TYPE_3__ Opcode ;

/* Variables and functions */
 int OT_BYTE ; 
 int OT_CONSTANT ; 
 int OT_DWORD ; 
 int OT_MEMORY ; 
 int OT_QWORD ; 
 int OT_WORD ; 
 int /*<<< orphan*/  eprintf (char*) ; 
 int /*<<< orphan*/  is_valid_registers (TYPE_3__ const*) ; 

__attribute__((used)) static int optest(RAsm *a, ut8 *data, const Opcode *op) {
	is_valid_registers (op);
	int l = 0;
	if (!op->operands[0].type || !op->operands[1].type) {
		eprintf ("Error: Invalid operands\n");
		return -1;
	}
	if (a->bits == 64) {
		if (op->operands[0].type & OT_MEMORY &&
			op->operands[0].reg_size & OT_DWORD) {
			data[l++] = 0x67;
		}
		if (op->operands[0].type & OT_QWORD) {
			if (op->operands[0].extended &&
				op->operands[1].extended) {
				data[l++] = 0x4d;
			} else {
				data[l++] = 0x48;
			}
		}
	}

	if (op->operands[1].type & OT_CONSTANT) {
		if (op->operands[0].type & OT_BYTE) {
			data[l++] = 0xf6;
		} else {
			if (op->operands[0].type & OT_WORD && a->bits != 16) {
				data[l++] = 0x66;
			}
			data[l++] = 0xf7;
		}
		if (op->operands[0].type & OT_MEMORY) {
			data[l++] = 0x00 | op->operands[0].reg;
		} else {
			data[l++] = 0xc0 | op->operands[0].reg;
		}
		data[l++] = op->operands[1].immediate >> 0;
		if (op->operands[0].type & OT_BYTE) {
			return l;
		}
		data[l++] = op->operands[1].immediate >> 8;
		if (op->operands[0].type & OT_WORD) {
			return l;
		}
		data[l++] = op->operands[1].immediate >> 16;
		data[l++] = op->operands[1].immediate >> 24;
		return l;
	}
	if (op->operands[0].type & OT_BYTE ||
		op->operands[1].type & OT_BYTE) {
		data[l++] = 0x84;
	} else {
		data[l++] = 0x85;
	}
	if (op->operands[0].type & OT_MEMORY) {
		data[l++] = 0x00 | op->operands[1].reg << 3 | op->operands[0].regs[0];
	} else {
		if (op->operands[1].type & OT_MEMORY) {
			data[l++] = 0x00 | op->operands[0].reg << 3 | op->operands[1].regs[0];
		} else {
			data[l++] = 0xc0 | op->operands[1].reg << 3 | op->operands[0].reg;
		}
	}
	return l;
}