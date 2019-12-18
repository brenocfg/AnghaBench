#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_2__* opcodes; } ;
typedef  TYPE_1__ zend_op_array ;
struct TYPE_7__ {scalar_t__ opcode; } ;
typedef  TYPE_2__ zend_op ;
struct TYPE_8__ {int len; int start; } ;
typedef  TYPE_3__ zend_basic_block ;

/* Variables and functions */
 scalar_t__ ZEND_NOP ; 

__attribute__((used)) static void compress_block(zend_op_array *op_array, zend_basic_block *block)
{
	while (block->len > 0) {
		zend_op *opline = &op_array->opcodes[block->start + block->len - 1];

		if (opline->opcode == ZEND_NOP) {
			block->len--;
		} else {
			break;
		}
	}
}