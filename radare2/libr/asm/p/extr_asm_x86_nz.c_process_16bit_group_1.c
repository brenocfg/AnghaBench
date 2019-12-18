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
struct TYPE_5__ {int immediate; int sign; int reg; } ;
typedef  int /*<<< orphan*/  RAsm ;
typedef  TYPE_2__ Opcode ;

/* Variables and functions */
 int X86R_AX ; 
 int /*<<< orphan*/  is_valid_registers (TYPE_2__ const*) ; 

__attribute__((used)) static int process_16bit_group_1(RAsm *a, ut8 *data, const Opcode *op, int op1) {
	is_valid_registers (op);
	int l = 0;
	int immediate = op->operands[1].immediate * op->operands[1].sign;

	data[l++] = 0x66;
	if (op->operands[1].immediate < 128) {
		data[l++] = 0x83;
		data[l++] = op->operands[0].reg | (0xc0 + op1 + op->operands[0].reg);
	} else {
		if (op->operands[0].reg == X86R_AX) {
			data[l++] = 0x05 + op1;
		} else {
			data[l++] = 0x81;
			data[l++] = (0xc0 + op1) | op->operands[0].reg;
		}
	}
	data[l++] = immediate;
	if (op->operands[1].immediate > 127) {
		data[l++] = immediate >> 8;
	}

	return l;
}