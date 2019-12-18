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
struct TYPE_5__ {int reg; int type; int dest_size; scalar_t__ extended; scalar_t__ explicit_size; } ;
typedef  int /*<<< orphan*/  RAsm ;
typedef  TYPE_2__ Opcode ;

/* Variables and functions */
 int ALL_SIZE ; 
 int OT_QWORD ; 
 int X86R_UNDEFINED ; 
 int /*<<< orphan*/  is_valid_registers (TYPE_2__ const*) ; 

__attribute__((used)) static int opnot(RAsm *a, ut8 * data, const Opcode *op) {
	is_valid_registers (op);
	int l = 0;

	if (op->operands[0].reg == X86R_UNDEFINED)  {
		return -1;
	}

	int size = op->operands[0].type & ALL_SIZE;
	if (op->operands[0].explicit_size) {
		size = op->operands[0].dest_size;
	}
	//rex prefix
	int rex = 1 << 6;
	bool use_rex = false;
	if (size & OT_QWORD) {			//W field
		use_rex = true;
		rex |= 1 << 3;
	}
	if (op->operands[0].extended) {		//B field
		use_rex = true;
		rex |= 1;
	}

	if (use_rex) {
		data[l++] = rex;
	}
	data[l++] = 0xf7;
	data[l++] = 0xd0 | op->operands[0].reg;

	return l;
}