#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_3__ ;
typedef  struct TYPE_14__   TYPE_2__ ;
typedef  struct TYPE_13__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zval ;
typedef  int /*<<< orphan*/  zend_string ;
struct TYPE_13__ {int fn_flags; } ;
struct TYPE_14__ {TYPE_1__ common; } ;
typedef  TYPE_2__ zend_function ;
struct TYPE_15__ {int /*<<< orphan*/  ce_flags; int /*<<< orphan*/  function_table; } ;
typedef  TYPE_3__ zend_class_entry ;

/* Variables and functions */
 scalar_t__ UNEXPECTED (int) ; 
 int ZEND_ACC_ABSTRACT ; 
 int /*<<< orphan*/  ZEND_ACC_IMPLICIT_ABSTRACT_CLASS ; 
 scalar_t__ Z_PTR_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  do_inheritance_check_on_method (TYPE_2__*,TYPE_2__*,TYPE_3__*,int /*<<< orphan*/ *) ; 
 TYPE_2__* zend_duplicate_function (TYPE_2__*,TYPE_3__*) ; 
 int /*<<< orphan*/ * zend_hash_find_ex (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static zend_function *do_inherit_method(zend_string *key, zend_function *parent, zend_class_entry *ce) /* {{{ */
{
	zval *child = zend_hash_find_ex(&ce->function_table, key, 1);

	if (child) {
		zend_function *func = (zend_function*)Z_PTR_P(child);

		if (UNEXPECTED(func == parent)) {
			/* The same method in interface may be inherited few times */
			return NULL;
		}

		do_inheritance_check_on_method(func, parent, ce, child);
		return NULL;
	}

	if (parent->common.fn_flags & (ZEND_ACC_ABSTRACT)) {
		ce->ce_flags |= ZEND_ACC_IMPLICIT_ABSTRACT_CLASS;
	}

	return zend_duplicate_function(parent, ce);
}