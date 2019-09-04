#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int ut8 ;
struct TYPE_5__ {int operands_count; TYPE_1__* operands; } ;
struct TYPE_4__ {int type; int* regs; int reg; } ;
typedef  int /*<<< orphan*/  RAsm ;
typedef  TYPE_2__ Opcode ;

/* Variables and functions */
 int OT_DWORD ; 
 int OT_FPUREG ; 
 int OT_MEMORY ; 
 int OT_QWORD ; 
 int OT_REGALL ; 

__attribute__((used)) static int opfsub(RAsm *a, ut8 *data, const Opcode *op) {
	int l = 0;
	switch (op->operands_count) {
	case 1:
		if ( op->operands[0].type & OT_MEMORY ) {
			if ( op->operands[0].type & OT_DWORD ) {
				data[l++] = 0xd8;
				data[l++] = 0x20 | op->operands[0].regs[0];
			} else if ( op->operands[0].type & OT_QWORD ) {
				data[l++] = 0xdc;
				data[l++] = 0x20 | op->operands[0].regs[0];
			} else {
				return -1;
			}
		} else {
			return -1;
		}
		break;
	case 2:
		if ( op->operands[0].type & OT_FPUREG & ~OT_REGALL && op->operands[0].reg == 0 &&
		     op->operands[1].type & OT_FPUREG & ~OT_REGALL ) {
			data[l++] = 0xd8;
			data[l++] = 0xe0 | op->operands[1].reg;
		} else if ( op->operands[0].type & OT_FPUREG & ~OT_REGALL &&
			    op->operands[1].type & OT_FPUREG & ~OT_REGALL && op->operands[1].reg == 0 ) {
			data[l++] = 0xdc;
			data[l++] = 0xe8 | op->operands[0].reg;
		} else {
			return -1;
		}
		break;
	default:
		return -1;
	}
	return l;
}