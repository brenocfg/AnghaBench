#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zend_script ;
typedef  int /*<<< orphan*/  zend_op_array ;
typedef  int /*<<< orphan*/  zend_func_info ;
struct TYPE_4__ {scalar_t__ op_arrays_count; int /*<<< orphan*/ * func_infos; int /*<<< orphan*/ ** op_arrays; } ;
typedef  TYPE_1__ zend_call_graph ;
typedef  int /*<<< orphan*/  zend_arena ;

/* Variables and functions */
 int FAILURE ; 
 scalar_t__ SUCCESS ; 
 scalar_t__ zend_arena_calloc (int /*<<< orphan*/ **,scalar_t__,int) ; 
 scalar_t__ zend_foreach_op_array (TYPE_1__*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zend_op_array_calc ; 
 int /*<<< orphan*/  zend_op_array_collect ; 

int zend_build_call_graph(zend_arena **arena, zend_script *script, zend_call_graph *call_graph) /* {{{ */
{
	call_graph->op_arrays_count = 0;
	if (zend_foreach_op_array(call_graph, script, zend_op_array_calc) != SUCCESS) {
		return FAILURE;
	}
	call_graph->op_arrays = (zend_op_array**)zend_arena_calloc(arena, call_graph->op_arrays_count, sizeof(zend_op_array*));
	call_graph->func_infos = (zend_func_info*)zend_arena_calloc(arena, call_graph->op_arrays_count, sizeof(zend_func_info));
	call_graph->op_arrays_count = 0;
	if (zend_foreach_op_array(call_graph, script, zend_op_array_collect) != SUCCESS) {
		return FAILURE;
	}

	return SUCCESS;
}