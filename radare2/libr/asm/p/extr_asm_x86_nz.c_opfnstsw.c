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
struct TYPE_4__ {int type; int* regs; int /*<<< orphan*/  reg; } ;
typedef  int /*<<< orphan*/  RAsm ;
typedef  TYPE_2__ Opcode ;

/* Variables and functions */
 int OT_GPREG ; 
 int OT_MEMORY ; 
 int OT_WORD ; 
 int /*<<< orphan*/  X86R_AX ; 

__attribute__((used)) static int opfnstsw(RAsm *a, ut8 *data, const Opcode *op) {
	int l = 0;
	switch (op->operands_count) {
	case 1:
		if ( op->operands[0].type & OT_MEMORY &&
		     op->operands[0].type & OT_WORD ) {
			data[l++] = 0xdd;
			data[l++] = 0x38 | op->operands[0].regs[0];
		} else if ( op->operands[0].type & OT_GPREG &&
			    op->operands[0].type & OT_WORD  &&
			    op->operands[0].reg == X86R_AX ) {
			data[l++] = 0xdf;
			data[l++] = 0xe0;
		} else {
			return -1;
		}
		break;
	default:
		return -1;
	}
	return l;
}