#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
struct TYPE_11__ {size_t result_def; } ;
typedef  TYPE_3__ zend_ssa_op ;
struct TYPE_12__ {int /*<<< orphan*/ * opcodes; } ;
typedef  TYPE_4__ zend_op_array ;
typedef  int /*<<< orphan*/  zend_op ;
struct TYPE_9__ {TYPE_2__* var_info; TYPE_3__* ops; } ;
struct TYPE_13__ {TYPE_1__ ssa; } ;
typedef  TYPE_5__ zend_func_info ;
typedef  int zend_bool ;
typedef  int uint32_t ;
struct TYPE_10__ {int type; } ;

/* Variables and functions */
 int MAY_BE_ARRAY ; 
 int MAY_BE_OBJECT ; 
 int MAY_BE_REF ; 
 int MAY_BE_RESOURCE ; 
 int MAY_BE_STRING ; 
 TYPE_5__* ZEND_FUNC_INFO (TYPE_4__*) ; 

__attribute__((used)) static zend_bool needs_live_range(zend_op_array *op_array, zend_op *def_opline) {
	zend_func_info *func_info = ZEND_FUNC_INFO(op_array);
	zend_ssa_op *ssa_op = &func_info->ssa.ops[def_opline - op_array->opcodes];
	if (ssa_op->result_def >= 0) {
		uint32_t type = func_info->ssa.var_info[ssa_op->result_def].type;
		return (type & (MAY_BE_STRING|MAY_BE_ARRAY|MAY_BE_OBJECT|MAY_BE_RESOURCE|MAY_BE_REF)) != 0;
	}
	return 1;
}