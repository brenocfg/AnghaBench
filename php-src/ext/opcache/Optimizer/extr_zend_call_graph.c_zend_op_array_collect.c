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
typedef  int /*<<< orphan*/  zend_op_array ;
struct TYPE_5__ {size_t num; int num_args; int return_value_used; } ;
typedef  TYPE_1__ zend_func_info ;
struct TYPE_6__ {int op_arrays_count; int /*<<< orphan*/ ** op_arrays; TYPE_1__* func_infos; } ;
typedef  TYPE_2__ zend_call_graph ;

/* Variables and functions */
 int SUCCESS ; 
 int /*<<< orphan*/  ZEND_SET_FUNC_INFO (int /*<<< orphan*/ *,TYPE_1__*) ; 

__attribute__((used)) static int zend_op_array_collect(zend_call_graph *call_graph, zend_op_array *op_array)
{
    zend_func_info *func_info = call_graph->func_infos + call_graph->op_arrays_count;

	ZEND_SET_FUNC_INFO(op_array, func_info);
	call_graph->op_arrays[call_graph->op_arrays_count] = op_array;
	func_info->num = call_graph->op_arrays_count;
	func_info->num_args = -1;
	func_info->return_value_used = -1;
	call_graph->op_arrays_count++;
	return SUCCESS;
}