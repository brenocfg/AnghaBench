#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int ut8 ;
typedef  int ut64 ;
typedef  int ut32 ;
typedef  int st32 ;
struct TYPE_8__ {TYPE_1__* operands; } ;
struct TYPE_7__ {int bits; int pc; } ;
struct TYPE_6__ {int type; int* regs; int offset; int reg; int offset_sign; } ;
typedef  TYPE_2__ RAsm ;
typedef  TYPE_3__ Opcode ;

/* Variables and functions */
 int OT_CONSTANT ; 
 int OT_MEMORY ; 
 int OT_REGALL ; 
 int X86R_EBP ; 
 int X86R_ESP ; 
 int X86R_UNDEFINED ; 

__attribute__((used)) static int oplea(RAsm *a, ut8 *data, const Opcode *op){
	int l = 0;
	int mod = 0;
	st32 offset = 0;
	int reg = 0;
	int rm = 0;
	if (op->operands[0].type & OT_REGALL &&
	    op->operands[1].type & (OT_MEMORY | OT_CONSTANT)) {
		if (a->bits == 64) {
			data[l++] = 0x48;
		}
		data[l++] = 0x8d;
		if (op->operands[1].regs[0] == X86R_UNDEFINED) {
			// RIP-relative LEA
			ut64 offset = op->operands[1].offset - a->pc;
			if (data[0] == 0x48) {
				offset -= 7;
			}
			ut32 high = 0xff00 & offset;
			data[l++] = op->operands[0].reg << 3 | 5;
			data[l++] = offset;
			data[l++] = high >> 8;
			data[l++] = offset >> 16;
			data[l++] = offset >> 24;
			return l;
		} else {
			reg = op->operands[0].reg;
			rm = op->operands[1].regs[0];

			offset = op->operands[1].offset * op->operands[1].offset_sign;
			if (offset != 0 || op->operands[1].regs[0] == X86R_EBP) {
				mod = 1;
				if (offset >= 128 || offset < -128) {
					mod = 2;
				}
				data[l++] = mod << 6 | reg << 3 | rm;
				if (op->operands[1].regs[0] == X86R_ESP) {
					data[l++] = 0x24;
				}
				data[l++] = offset;
				if (mod == 2) {
					data[l++] = offset >> 8;
					data[l++] = offset >> 16;
					data[l++] = offset >> 24;
				}
			} else {
				data[l++] = op->operands[0].reg << 3 | op->operands[1].regs[0];
				if (op->operands[1].regs[0] == X86R_ESP) {
					data[l++] = 0x24;
				}
			}

		}
	}
	return l;
}