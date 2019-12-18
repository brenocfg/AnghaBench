#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_5__ ;
typedef  struct TYPE_11__   TYPE_4__ ;
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zval ;
struct TYPE_9__ {int /*<<< orphan*/  name; } ;
typedef  TYPE_2__ zend_internal_arg_info ;
struct TYPE_8__ {int fn_flags; int /*<<< orphan*/  scope; } ;
struct TYPE_10__ {scalar_t__ type; TYPE_1__ common; } ;
typedef  TYPE_3__ zend_function ;
typedef  int /*<<< orphan*/  zend_bool ;
typedef  int /*<<< orphan*/  uint32_t ;
struct _zend_arg_info {int /*<<< orphan*/  name; } ;
struct TYPE_11__ {int /*<<< orphan*/  obj; int /*<<< orphan*/  ce; int /*<<< orphan*/  ref_type; TYPE_5__* ptr; } ;
typedef  TYPE_4__ reflection_object ;
struct TYPE_12__ {TYPE_3__* fptr; int /*<<< orphan*/  required; int /*<<< orphan*/  offset; struct _zend_arg_info* arg_info; } ;
typedef  TYPE_5__ parameter_reference ;

/* Variables and functions */
 int /*<<< orphan*/  REF_TYPE_PARAMETER ; 
 int ZEND_ACC_USER_ARG_INFO ; 
 scalar_t__ ZEND_INTERNAL_FUNCTION ; 
 int /*<<< orphan*/  ZVAL_NULL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZVAL_OBJ (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZVAL_STRING (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZVAL_STR_COPY (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Z_ADDREF_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Z_OBJ_P (int /*<<< orphan*/ *) ; 
 TYPE_4__* Z_REFLECTION_P (int /*<<< orphan*/ *) ; 
 scalar_t__ emalloc (int) ; 
 int /*<<< orphan*/  reflection_instantiate (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reflection_parameter_ptr ; 
 int /*<<< orphan*/ * reflection_prop_name (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void reflection_parameter_factory(zend_function *fptr, zval *closure_object, struct _zend_arg_info *arg_info, uint32_t offset, zend_bool required, zval *object)
{
	reflection_object *intern;
	parameter_reference *reference;
	zval *prop_name;

	reflection_instantiate(reflection_parameter_ptr, object);
	intern = Z_REFLECTION_P(object);
	reference = (parameter_reference*) emalloc(sizeof(parameter_reference));
	reference->arg_info = arg_info;
	reference->offset = offset;
	reference->required = required;
	reference->fptr = fptr;
	intern->ptr = reference;
	intern->ref_type = REF_TYPE_PARAMETER;
	intern->ce = fptr->common.scope;
	if (closure_object) {
		Z_ADDREF_P(closure_object);
		ZVAL_OBJ(&intern->obj, Z_OBJ_P(closure_object));
	}

	prop_name = reflection_prop_name(object);
	if (arg_info->name) {
		if (fptr->type == ZEND_INTERNAL_FUNCTION &&
		    !(fptr->common.fn_flags & ZEND_ACC_USER_ARG_INFO)) {
			ZVAL_STRING(prop_name, ((zend_internal_arg_info*)arg_info)->name);
		} else {
			ZVAL_STR_COPY(prop_name, arg_info->name);
		}
	} else {
		ZVAL_NULL(prop_name);
	}
}