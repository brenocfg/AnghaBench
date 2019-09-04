#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zval ;
typedef  int zend_long ;
struct TYPE_6__ {int fn_flags; int /*<<< orphan*/  function_name; } ;
struct TYPE_7__ {TYPE_1__ common; } ;
typedef  TYPE_2__ zend_function ;
typedef  int /*<<< orphan*/  zend_class_entry ;

/* Variables and functions */
 int /*<<< orphan*/  Z_OBJ_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  add_next_index_zval (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ is_closure_invoke (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  reflection_method_factory (int /*<<< orphan*/ *,TYPE_2__*,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_2__* zend_get_closure_invoke_method (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void _addmethod(zend_function *mptr, zend_class_entry *ce, zval *retval, zend_long filter, zval *obj)
{
	zval method;
	zend_function *closure;
	if (mptr->common.fn_flags & filter) {
		if (obj && is_closure_invoke(ce, mptr->common.function_name)
			&& (closure = zend_get_closure_invoke_method(Z_OBJ_P(obj))) != NULL)
		{
			mptr = closure;
		}
		/* don't assign closure_object since we only reflect the invoke handler
		   method and not the closure definition itself, even if we have a
		   closure */
		reflection_method_factory(ce, mptr, NULL, &method);
		add_next_index_zval(retval, &method);
	}
}