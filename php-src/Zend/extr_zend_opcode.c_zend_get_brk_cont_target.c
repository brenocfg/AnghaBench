#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_6__ ;
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zend_op_array ;
struct TYPE_8__ {int num; } ;
struct TYPE_7__ {int num; } ;
struct TYPE_9__ {scalar_t__ opcode; TYPE_2__ op1; TYPE_1__ op2; } ;
typedef  TYPE_3__ zend_op ;
struct TYPE_10__ {int parent; int /*<<< orphan*/  cont; int /*<<< orphan*/  brk; } ;
typedef  TYPE_4__ zend_brk_cont_element ;
typedef  int /*<<< orphan*/  uint32_t ;
struct TYPE_11__ {TYPE_4__* brk_cont_array; } ;

/* Variables and functions */
 TYPE_6__ CG (int /*<<< orphan*/ ) ; 
 scalar_t__ ZEND_BRK ; 
 int /*<<< orphan*/  context ; 

__attribute__((used)) static uint32_t zend_get_brk_cont_target(const zend_op_array *op_array, const zend_op *opline) {
	int nest_levels = opline->op2.num;
	int array_offset = opline->op1.num;
	zend_brk_cont_element *jmp_to;
	do {
		jmp_to = &CG(context).brk_cont_array[array_offset];
		if (nest_levels > 1) {
			array_offset = jmp_to->parent;
		}
	} while (--nest_levels > 0);

	return opline->opcode == ZEND_BRK ? jmp_to->brk : jmp_to->cont;
}