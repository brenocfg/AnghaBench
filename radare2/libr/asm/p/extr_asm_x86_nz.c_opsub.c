#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_6__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  ut8 ;
struct TYPE_8__ {int type; } ;
struct TYPE_7__ {TYPE_6__* operands; } ;
typedef  int /*<<< orphan*/  RAsm ;
typedef  TYPE_1__ Opcode ;

/* Variables and functions */
 int OT_CONSTANT ; 
 int OT_GPREG ; 
 int OT_WORD ; 
 int /*<<< orphan*/  is_al_reg (TYPE_6__*) ; 
 int process_16bit_group_1 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__ const*,int) ; 
 int process_1byte_op (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__ const*,int) ; 
 int process_group_1 (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__ const*) ; 

__attribute__((used)) static int opsub(RAsm *a, ut8 *data, const Opcode *op) {
	if (op->operands[1].type & OT_CONSTANT) {
		if (op->operands[0].type & OT_GPREG &&
		    op->operands[0].type & OT_WORD) {
			return process_16bit_group_1 (a, data, op, 0x28);
		}
		if (!is_al_reg (&op->operands[0])) {
			return process_group_1 (a, data, op);
		}
	}
	return process_1byte_op (a, data, op, 0x28);
}