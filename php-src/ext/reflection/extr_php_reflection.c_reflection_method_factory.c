#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zval ;
struct TYPE_9__ {TYPE_1__* scope; int /*<<< orphan*/  function_name; } ;
struct TYPE_10__ {TYPE_2__ common; } ;
typedef  TYPE_3__ zend_function ;
typedef  int /*<<< orphan*/  zend_class_entry ;
struct TYPE_11__ {int /*<<< orphan*/  obj; int /*<<< orphan*/ * ce; int /*<<< orphan*/  ref_type; TYPE_3__* ptr; } ;
typedef  TYPE_4__ reflection_object ;
struct TYPE_8__ {int /*<<< orphan*/  name; scalar_t__ trait_aliases; } ;

/* Variables and functions */
 int /*<<< orphan*/  REF_TYPE_FUNCTION ; 
 int /*<<< orphan*/  ZVAL_OBJ (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZVAL_STR_COPY (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Z_ADDREF_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Z_OBJ_P (int /*<<< orphan*/ *) ; 
 TYPE_4__* Z_REFLECTION_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reflection_instantiate (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reflection_method_ptr ; 
 int /*<<< orphan*/  reflection_prop_class (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reflection_prop_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zend_resolve_method_name (int /*<<< orphan*/ *,TYPE_3__*) ; 

__attribute__((used)) static void reflection_method_factory(zend_class_entry *ce, zend_function *method, zval *closure_object, zval *object)
{
	reflection_object *intern;

	reflection_instantiate(reflection_method_ptr, object);
	intern = Z_REFLECTION_P(object);
	intern->ptr = method;
	intern->ref_type = REF_TYPE_FUNCTION;
	intern->ce = ce;
	if (closure_object) {
		Z_ADDREF_P(closure_object);
		ZVAL_OBJ(&intern->obj, Z_OBJ_P(closure_object));
	}

	ZVAL_STR_COPY(reflection_prop_name(object),
		(method->common.scope && method->common.scope->trait_aliases)
			? zend_resolve_method_name(ce, method) : method->common.function_name);
	ZVAL_STR_COPY(reflection_prop_class(object), method->common.scope->name);
}