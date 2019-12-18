#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
struct TYPE_14__ {TYPE_2__* ops; TYPE_1__* var_info; } ;
typedef  TYPE_3__ zend_ssa ;
struct TYPE_15__ {int flags; } ;
typedef  TYPE_4__ zend_property_info ;
struct TYPE_16__ {int /*<<< orphan*/ * scope; } ;
typedef  TYPE_5__ zend_op_array ;
struct TYPE_17__ {scalar_t__ op2_type; scalar_t__ op1_type; int /*<<< orphan*/  op2; } ;
typedef  TYPE_6__ zend_op ;
typedef  int /*<<< orphan*/  zend_class_entry ;
struct TYPE_13__ {size_t op1_use; } ;
struct TYPE_12__ {int /*<<< orphan*/ * ce; } ;

/* Variables and functions */
 int /*<<< orphan*/  CRT_CONSTANT (int /*<<< orphan*/ ) ; 
 scalar_t__ IS_CONST ; 
 scalar_t__ IS_UNUSED ; 
 int ZEND_ACC_STATIC ; 
 int /*<<< orphan*/  Z_STR_P (int /*<<< orphan*/ ) ; 
 TYPE_4__* lookup_prop_info (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static zend_property_info *zend_fetch_prop_info(const zend_op_array *op_array, zend_ssa *ssa, zend_op *opline, int i)
{
	zend_property_info *prop_info = NULL;
	if (opline->op2_type == IS_CONST) {
		zend_class_entry *ce = NULL;

		if (opline->op1_type == IS_UNUSED) {
			ce = op_array->scope;
		} else if (ssa->ops[i].op1_use >= 0) {
			ce = ssa->var_info[ssa->ops[i].op1_use].ce;
		}
		if (ce) {
			prop_info = lookup_prop_info(ce,
				Z_STR_P(CRT_CONSTANT(opline->op2)),
				op_array->scope);
			if (prop_info && (prop_info->flags & ZEND_ACC_STATIC)) {
				prop_info = NULL;
			}
		}
	}
	return prop_info;
}