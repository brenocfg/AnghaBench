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
struct TYPE_6__ {TYPE_1__* operands; } ;
struct TYPE_5__ {int type; int reg; int offset; int offset_sign; int* regs; } ;
typedef  int /*<<< orphan*/  RAsm ;
typedef  TYPE_2__ Opcode ;

/* Variables and functions */
 int OT_GPREG ; 
 int OT_MEMORY ; 
 int OT_REGTYPE ; 
 int OT_SEGMENTREG ; 
 int X86R_EBP ; 
 int X86R_ESP ; 
 int X86R_FS ; 
 int /*<<< orphan*/  is_valid_registers (TYPE_2__ const*) ; 

__attribute__((used)) static int oppop(RAsm *a, ut8 *data, const Opcode *op) {
	is_valid_registers (op);
	int l = 0;
	int offset = 0;
	int mod = 0;
	if (op->operands[0].type & OT_GPREG) {
		if (op->operands[0].type & OT_MEMORY) {
			return -1;
		}
		if (op->operands[0].type & OT_REGTYPE & OT_SEGMENTREG) {
			ut8 base;
			if (op->operands[0].reg & X86R_FS) {
				data[l++] = 0x0f;
				base = 0x81;
			} else {
				base = 0x7;
			}
			data[l++] = base + (8 * op->operands[0].reg);
		} else {
			ut8 base = 0x58;
			data[l++] = base + op->operands[0].reg;
		}
	} else if (op->operands[0].type & OT_MEMORY) {
		data[l++] = 0x8f;
		offset = op->operands[0].offset * op->operands[0].offset_sign;
		if (offset != 0 || op->operands[0].regs[0] == X86R_EBP) {
			mod = 1;
			if (offset >= 128 || offset < -128) {
				mod = 2;
			}
			data[l++] = mod << 6 | op->operands[0].regs[0];
			if (op->operands[0].regs[0] == X86R_ESP) {
				data[l++] = 0x24;
			}
			data[l++] = offset;
			if (mod == 2) {
				data[l++] = offset >> 8;
				data[l++] = offset >> 16;
				data[l++] = offset >> 24;
			}
		} else {
			data[l++] = op->operands[0].regs[0];
			if (op->operands[0].regs[0] == X86R_ESP) {
				data[l++] = 0x24;
			}
		}

	}
	return l;
}