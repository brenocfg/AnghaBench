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
struct TYPE_7__ {int type; int reg; int offset; int offset_sign; int* regs; int immediate; int sign; scalar_t__ extended; } ;
typedef  TYPE_2__ RAsm ;
typedef  TYPE_3__ Opcode ;

/* Variables and functions */
 int OT_GPREG ; 
 int OT_MEMORY ; 
 int OT_REGTYPE ; 
 int OT_SEGMENTREG ; 
 int X86R_EBP ; 
 int X86R_ESP ; 
 int X86R_FS ; 
 int /*<<< orphan*/  is_valid_registers (TYPE_3__ const*) ; 

__attribute__((used)) static int oppush(RAsm *a, ut8 *data, const Opcode *op) {
	is_valid_registers (op);
	int l = 0;
	int mod = 0;
	st32 immediate = 0;;
	st32 offset = 0;
	if (op->operands[0].type & OT_GPREG &&
	    !(op->operands[0].type & OT_MEMORY)) {
		if (op->operands[0].type & OT_REGTYPE & OT_SEGMENTREG) {
			ut8 base;
			if (op->operands[0].reg & X86R_FS) {
				data[l++] = 0x0f;
				base = 0x80;
			} else {
				base = 0x6;
			}
			data[l++] = base + (8 * op->operands[0].reg);
		} else {
			if (op->operands[0].extended && a->bits == 64) {
				data[l++] = 0x41;
			}
			ut8 base = 0x50;
			data[l++] = base + op->operands[0].reg;
		}
	} else if (op->operands[0].type & OT_MEMORY) {
		data[l++] = 0xff;
		offset = op->operands[0].offset * op->operands[0].offset_sign;
		if (offset != 0 || op->operands[0].regs[0] == X86R_EBP) {
			mod = 1;
			if (offset >= 128 || offset < -128) {
				mod = 2;
			}
			data[l++] = mod << 6 | 6 << 3 | op->operands[0].regs[0];
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
			mod = 3;
			data[l++] = mod << 4 | op->operands[0].regs[0];
			if (op->operands[0].regs[0] == X86R_ESP) {
				data[l++] = 0x24;
			}
		}
	} else {
		immediate = op->operands[0].immediate * op->operands[0].sign;
		if (immediate >= 128 || immediate < -128) {
			data[l++] = 0x68;
			data[l++] = immediate;
			data[l++] = immediate >> 8;
			data[l++] = immediate >> 16;
			data[l++] = immediate >> 24;
		} else {
			data[l++] = 0x6a;
			data[l++] = immediate;
		}
	}
	return l;
}