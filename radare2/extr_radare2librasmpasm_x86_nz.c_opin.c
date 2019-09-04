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
struct TYPE_5__ {scalar_t__ reg; int type; int immediate; int sign; } ;
typedef  int /*<<< orphan*/  RAsm ;
typedef  TYPE_2__ Opcode ;

/* Variables and functions */
 int OT_BYTE ; 
 int OT_CONSTANT ; 
 int OT_DWORD ; 
 int OT_WORD ; 
 scalar_t__ X86R_AL ; 
 scalar_t__ X86R_AX ; 
 scalar_t__ X86R_DX ; 
 scalar_t__ X86R_EAX ; 
 int /*<<< orphan*/  is_valid_registers (TYPE_2__ const*) ; 

__attribute__((used)) static int opin(RAsm *a, ut8 *data, const Opcode *op) {
	is_valid_registers (op);
	int l = 0;
	st32 immediate = 0;
	if (op->operands[1].reg == X86R_DX) {
		if (op->operands[0].reg == X86R_AL &&
			op->operands[0].type & OT_BYTE) {
			data[l++] = 0xec;
			return l;
		}
		if (op->operands[0].reg == X86R_AX &&
			op->operands[0].type & OT_WORD) {
			data[l++] = 0x66;
			data[l++] = 0xed;
			return l;
		}
		if (op->operands[0].reg == X86R_EAX &&
			op->operands[0].type & OT_DWORD) {
			data[l++] = 0xed;
			return l;
		}
	} else if (op->operands[1].type & OT_CONSTANT) {
		immediate = op->operands[1].immediate * op->operands[1].sign;
		if (immediate > 255 || immediate < -128) {
			return -1;
		}
		if (op->operands[0].reg == X86R_AL &&
			op->operands[0].type & OT_BYTE) {
			data[l++] = 0xe4;
		} else if (op->operands[0].reg == X86R_AX &&
				   op->operands[0].type & OT_BYTE) {
			data[l++] = 0x66;
			data[l++] = 0xe5;
		} else if (op->operands[0].reg == X86R_EAX &&
				   op->operands[0].type & OT_DWORD) {
			data[l++] = 0xe5;
		}
		data[l++] = immediate;
	}
	return l;
}