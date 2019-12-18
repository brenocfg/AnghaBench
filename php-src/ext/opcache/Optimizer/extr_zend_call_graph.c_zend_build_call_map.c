#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_10__ {size_t opcodes; int /*<<< orphan*/  last; } ;
typedef  TYPE_2__ zend_op_array ;
struct TYPE_11__ {TYPE_4__* callee_info; } ;
typedef  TYPE_3__ zend_func_info ;
struct TYPE_12__ {size_t caller_init_opline; size_t caller_call_opline; int num_args; TYPE_1__* arg_info; struct TYPE_12__* next_callee; } ;
typedef  TYPE_4__ zend_call_info ;
typedef  int /*<<< orphan*/  zend_arena ;
struct TYPE_9__ {size_t opline; } ;

/* Variables and functions */
 TYPE_4__** zend_arena_calloc (int /*<<< orphan*/ **,int,int /*<<< orphan*/ ) ; 

zend_call_info **zend_build_call_map(zend_arena **arena, zend_func_info *info, zend_op_array *op_array) /* {{{ */
{
	zend_call_info **map, *call;
	if (!info->callee_info) {
		/* Don't build call map if function contains no calls */
		return NULL;
	}

	map = zend_arena_calloc(arena, sizeof(zend_call_info *), op_array->last);
	for (call = info->callee_info; call; call = call->next_callee) {
		int i;
		map[call->caller_init_opline - op_array->opcodes] = call;
		map[call->caller_call_opline - op_array->opcodes] = call;
		for (i = 0; i < call->num_args; i++) {
			if (call->arg_info[i].opline) {
				map[call->arg_info[i].opline - op_array->opcodes] = call;
			}
		}
	}
	return map;
}