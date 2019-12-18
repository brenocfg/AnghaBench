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
struct TYPE_4__ {int type; int* regs; } ;
typedef  int /*<<< orphan*/  RAsm ;
typedef  TYPE_2__ Opcode ;

/* Variables and functions */
 int OT_MEMORY ; 
 int OT_WORD ; 

__attribute__((used)) static int opfldcw(RAsm *a, ut8 *data, const Opcode *op) {
	int l = 0;
	switch (op->operands_count) {
	case 1:
		if ( op->operands[0].type & OT_MEMORY &&
		     op->operands[0].type & OT_WORD ) {
			data[l++] = 0xd9;
			data[l++] = 0x28 | op->operands[0].regs[0];
		} else {
			return -1;
		}
		break;
	default:
		return -1;
	}
	return l;
}