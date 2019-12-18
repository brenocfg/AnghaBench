#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_4__ ;
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct TYPE_7__ {scalar_t__ static_variables; } ;
struct TYPE_8__ {int fn_flags; TYPE_4__* scope; } ;
struct TYPE_9__ {scalar_t__ type; TYPE_1__ op_array; TYPE_2__ common; } ;
typedef  TYPE_3__ zend_function ;
struct TYPE_10__ {int ce_flags; } ;
typedef  TYPE_4__ zend_class_entry ;

/* Variables and functions */
 int ZEND_ACC_ABSTRACT ; 
 int ZEND_ACC_IMPLICIT_ABSTRACT_CLASS ; 
 int ZEND_ACC_TRAIT ; 
 int ZEND_HAS_STATIC_IN_METHODS ; 
 scalar_t__ ZEND_USER_FUNCTION ; 

__attribute__((used)) static void zend_fixup_trait_method(zend_function *fn, zend_class_entry *ce) /* {{{ */
{
	if ((fn->common.scope->ce_flags & ZEND_ACC_TRAIT) == ZEND_ACC_TRAIT) {

		fn->common.scope = ce;

		if (fn->common.fn_flags & ZEND_ACC_ABSTRACT) {
			ce->ce_flags |= ZEND_ACC_IMPLICIT_ABSTRACT_CLASS;
		}
		if (fn->type == ZEND_USER_FUNCTION && fn->op_array.static_variables) {
			ce->ce_flags |= ZEND_HAS_STATIC_IN_METHODS;
		}
	}
}