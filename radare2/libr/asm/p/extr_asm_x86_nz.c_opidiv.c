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
struct TYPE_6__ {int operands_count; TYPE_1__* operands; } ;
struct TYPE_5__ {int type; int* regs; int reg; } ;
typedef  int /*<<< orphan*/  RAsm ;
typedef  TYPE_2__ Opcode ;

/* Variables and functions */
 int OT_BYTE ; 
 int OT_MEMORY ; 
 int OT_QWORD ; 
 int OT_WORD ; 
 int /*<<< orphan*/  is_valid_registers (TYPE_2__ const*) ; 

__attribute__((used)) static int opidiv(RAsm *a, ut8 *data, const Opcode *op) {
	is_valid_registers (op);
	int l = 0;

	if ( op->operands[0].type & OT_QWORD ) {
		data[l++] = 0x48;
	}
	switch (op->operands_count) {
	case 1:
		if ( op->operands[0].type & OT_WORD ) {
			data[l++] = 0x66;
		}
		if (op->operands[0].type & OT_BYTE) {
			data[l++] = 0xf6;
		} else {
			data[l++] = 0xf7;
		}
		if (op->operands[0].type & OT_MEMORY) {
			data[l++] = 0x38 | op->operands[0].regs[0];
		} else {
			data[l++] = 0xf8 | op->operands[0].reg;
		}
		break;
	default:
		return -1;
	}
	return l;
}