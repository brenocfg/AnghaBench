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
struct TYPE_9__ {int operands_count; TYPE_1__* operands; } ;
struct TYPE_8__ {int bits; } ;
struct TYPE_7__ {int type; int reg; } ;
typedef  TYPE_2__ RAsm ;
typedef  TYPE_3__ Opcode ;

/* Variables and functions */
 int OT_BYTE ; 
 int OT_REGALL ; 
 int /*<<< orphan*/  is_valid_registers (TYPE_3__ const*) ; 

__attribute__((used)) static int opxadd(RAsm *a, ut8 *data, const Opcode *op) {
	is_valid_registers (op);
	int i = 0;
	if (op->operands_count < 2 ) {
		return -1;
	}
	if (a->bits == 64) {
		data[i++] = 0x48;
	};
	data[i++] = 0x0f;
	if (op->operands[0].type & OT_BYTE &&
	   op->operands[1].type & OT_BYTE) {
		data[i++] = 0xc0;
	} else {
		data[i++] = 0xc1;
	}
	if (op->operands[0].type & OT_REGALL &&
       op->operands[1].type & OT_REGALL) { // TODO memory modes
		data[i] |= 0xc0;
		data[i] |= (op->operands[1].reg << 3);
		data[i++] |= op->operands[0].reg;
	}
	return i;
}