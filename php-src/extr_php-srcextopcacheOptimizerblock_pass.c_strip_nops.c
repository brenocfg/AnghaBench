#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_9__ {TYPE_3__* opcodes; } ;
typedef  TYPE_1__ zend_op_array ;
struct TYPE_10__ {size_t len; size_t start; } ;
typedef  TYPE_2__ zend_basic_block ;
typedef  size_t uint32_t ;
struct TYPE_11__ {scalar_t__ opcode; int op1_type; } ;

/* Variables and functions */
 int IS_CONST ; 
 int IS_CV ; 
 int /*<<< orphan*/  MAKE_NOP (TYPE_3__*) ; 
 scalar_t__ ZEND_JMPNZ ; 
 scalar_t__ ZEND_JMPZ ; 
 scalar_t__ ZEND_NOP ; 
 int /*<<< orphan*/  strip_leading_nops (TYPE_1__*,TYPE_2__*) ; 
 scalar_t__ zend_is_smart_branch (TYPE_3__*) ; 

__attribute__((used)) static void strip_nops(zend_op_array *op_array, zend_basic_block *b)
{
	uint32_t i, j;

	if (b->len == 0) {
		return;
	}

	if (op_array->opcodes[b->start].opcode == ZEND_NOP) {
		strip_leading_nops(op_array, b);
	}

	if (b->len == 0) {
		return;
	}

	/* strip the inside NOPs */
	i = j = b->start + 1;
	while (i < b->start + b->len) {
		if (op_array->opcodes[i].opcode != ZEND_NOP) {
			if (i != j) {
				op_array->opcodes[j] = op_array->opcodes[i];
			}
			j++;
		}
		if (i + 1 < b->start + b->len
		 && (op_array->opcodes[i+1].opcode == ZEND_JMPZ
		  || op_array->opcodes[i+1].opcode == ZEND_JMPNZ)
		 && op_array->opcodes[i+1].op1_type & (IS_CV|IS_CONST)
		 && zend_is_smart_branch(op_array->opcodes + j - 1)) {
			/* don't remove NOP, that splits incorrect smart branch */
			j++;
		}
		i++;
	}
	b->len = j - b->start;
	while (j < i) {
		MAKE_NOP(op_array->opcodes + j);
		j++;
	}
}