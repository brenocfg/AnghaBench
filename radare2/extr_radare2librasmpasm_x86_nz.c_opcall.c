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
typedef  scalar_t__ ut64 ;
struct TYPE_9__ {TYPE_1__* operands; } ;
struct TYPE_8__ {int bits; scalar_t__ pc; } ;
struct TYPE_7__ {int type; int reg; int* regs; int offset; int offset_sign; int immediate; int sign; scalar_t__ extended; } ;
typedef  TYPE_2__ RAsm ;
typedef  TYPE_3__ Opcode ;

/* Variables and functions */
 int OT_GPREG ; 
 int OT_MEMORY ; 
 int X86R_UNDEFINED ; 
 int /*<<< orphan*/  is_valid_registers (TYPE_3__ const*) ; 

__attribute__((used)) static int opcall(RAsm *a, ut8 *data, const Opcode *op) {
	is_valid_registers (op);
	int l = 0;
	int immediate = 0;
	int offset = 0;
	int mod = 0;

	if (op->operands[0].type & OT_GPREG) {
		if (op->operands[0].reg == X86R_UNDEFINED) {
			return -1;
		}
		if (a->bits == 64 && op->operands[0].extended) {
			data[l++] = 0x41;
		}
		data[l++] = 0xff;
		mod = 3;
		data[l++] = mod << 6 | 2 << 3 | op->operands[0].reg;
	} else if (op->operands[0].type & OT_MEMORY) {
		if (op->operands[0].regs[0] == X86R_UNDEFINED) {
			return -1;
		}
		data[l++] = 0xff;
		offset = op->operands[0].offset * op->operands[0].offset_sign;
		if (offset) {
			mod = 1;
			if (offset > 127 || offset < -128) {
				mod = 2;
			}
		}
		data[l++] = mod << 6 | 2 << 3 | op->operands[0].regs[0];
		if (mod) {
			data[l++] = offset;
			if (mod == 2) {
				data[l++] = offset >> 8;
				data[l++] = offset >> 16;
				data[l++] = offset >> 24;
			}
		}
	} else {
		ut64 instr_offset = a->pc;
		data[l++] = 0xe8;
		immediate = op->operands[0].immediate * op->operands[0].sign;
		immediate -= instr_offset + 5;
		data[l++] = immediate;
		data[l++] = immediate >> 8;
		data[l++] = immediate >> 16;
		data[l++] = immediate >> 24;
	}
	return l;
}