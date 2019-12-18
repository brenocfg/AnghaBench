#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_2__ ;
typedef  struct TYPE_11__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zend_string ;
struct TYPE_11__ {int /*<<< orphan*/  ce; } ;
typedef  TYPE_1__ zend_object ;
struct TYPE_12__ {int /*<<< orphan*/  obj; void* dest; void* src; int /*<<< orphan*/  error; } ;
typedef  TYPE_2__ php_converter_object ;
typedef  int /*<<< orphan*/  UErrorCode ;

/* Variables and functions */
 int /*<<< orphan*/  THROW_UFAILURE (TYPE_2__*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ U_FAILURE (int /*<<< orphan*/ ) ; 
 scalar_t__ U_SUCCESS (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  U_ZERO_ERROR ; 
 int /*<<< orphan*/  ZSTR_VAL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * intl_error_get_message (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  intl_errors_reset (int /*<<< orphan*/ *) ; 
 TYPE_2__* php_converter_fetch_object (TYPE_1__*) ; 
 TYPE_1__* php_converter_object_ctor (int /*<<< orphan*/ ,TYPE_2__**) ; 
 int /*<<< orphan*/  php_converter_set_callbacks (TYPE_2__*,void*) ; 
 void* ucnv_safeClone (void*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zend_objects_clone_members (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zend_string_release_ex (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zend_throw_exception (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static zend_object *php_converter_clone_object(zend_object *object) {
	php_converter_object *objval, *oldobj = php_converter_fetch_object(object);
	zend_object *retval = php_converter_object_ctor(object->ce, &objval);
	UErrorCode error = U_ZERO_ERROR;

	intl_errors_reset(&oldobj->error);

	objval->src = ucnv_safeClone(oldobj->src, NULL, NULL, &error);
	if (U_SUCCESS(error)) {
		error = U_ZERO_ERROR;
		objval->dest = ucnv_safeClone(oldobj->dest, NULL, NULL, &error);
	}
	if (U_FAILURE(error)) {
		zend_string *err_msg;
		THROW_UFAILURE(oldobj, "ucnv_safeClone", error);

		err_msg = intl_error_get_message(&oldobj->error);
		zend_throw_exception(NULL, ZSTR_VAL(err_msg), 0);
		zend_string_release_ex(err_msg, 0);

		return retval;
	}

	/* Update contexts for converter error handlers */
	php_converter_set_callbacks(objval, objval->src );
	php_converter_set_callbacks(objval, objval->dest);

	zend_objects_clone_members(&(objval->obj), &(oldobj->obj));

	/* Newly cloned object deliberately does not inherit error state from original object */

	return retval;
}