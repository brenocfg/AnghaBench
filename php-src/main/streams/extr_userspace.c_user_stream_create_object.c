#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_15__   TYPE_9__ ;
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zval ;
struct TYPE_12__ {void* object; int /*<<< orphan*/  called_scope; TYPE_2__* function_handler; } ;
typedef  TYPE_3__ zend_fcall_info_cache ;
struct TYPE_13__ {int size; int no_separation; int /*<<< orphan*/ * params; scalar_t__ param_count; int /*<<< orphan*/ * retval; void* object; int /*<<< orphan*/  function_name; } ;
typedef  TYPE_4__ zend_fcall_info ;
struct php_user_stream_wrapper {TYPE_9__* ce; } ;
struct TYPE_14__ {int /*<<< orphan*/  res; } ;
typedef  TYPE_5__ php_stream_context ;
typedef  int /*<<< orphan*/  fci ;
struct TYPE_15__ {int ce_flags; TYPE_2__* constructor; int /*<<< orphan*/  name; } ;
struct TYPE_10__ {int /*<<< orphan*/  function_name; } ;
struct TYPE_11__ {TYPE_1__ common; } ;

/* Variables and functions */
 int /*<<< orphan*/  E_WARNING ; 
 scalar_t__ FAILURE ; 
 int /*<<< orphan*/  GC_ADDREF (int /*<<< orphan*/ ) ; 
 int ZEND_ACC_EXPLICIT_ABSTRACT_CLASS ; 
 int ZEND_ACC_IMPLICIT_ABSTRACT_CLASS ; 
 int ZEND_ACC_INTERFACE ; 
 int ZEND_ACC_TRAIT ; 
 int /*<<< orphan*/  ZSTR_VAL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZVAL_UNDEF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Z_OBJCE_P (int /*<<< orphan*/ *) ; 
 void* Z_OBJ_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  add_property_null (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  add_property_resource (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ object_init_ex (int /*<<< orphan*/ *,TYPE_9__*) ; 
 int /*<<< orphan*/  php_error_docref (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ zend_call_function (TYPE_4__*,TYPE_3__*) ; 
 int /*<<< orphan*/  zval_ptr_dtor (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void user_stream_create_object(struct php_user_stream_wrapper *uwrap, php_stream_context *context, zval *object)
{
	if (uwrap->ce->ce_flags & (ZEND_ACC_INTERFACE|ZEND_ACC_TRAIT|ZEND_ACC_IMPLICIT_ABSTRACT_CLASS|ZEND_ACC_EXPLICIT_ABSTRACT_CLASS)) {
		ZVAL_UNDEF(object);
		return;
	}

	/* create an instance of our class */
	if (object_init_ex(object, uwrap->ce) == FAILURE) {
		ZVAL_UNDEF(object);
		return;
	}

	if (context) {
		add_property_resource(object, "context", context->res);
		GC_ADDREF(context->res);
	} else {
		add_property_null(object, "context");
	}

	if (uwrap->ce->constructor) {
		zend_fcall_info fci;
		zend_fcall_info_cache fcc;
		zval retval;

		fci.size = sizeof(fci);
		ZVAL_UNDEF(&fci.function_name);
		fci.object = Z_OBJ_P(object);
		fci.retval = &retval;
		fci.param_count = 0;
		fci.params = NULL;
		fci.no_separation = 1;

		fcc.function_handler = uwrap->ce->constructor;
		fcc.called_scope = Z_OBJCE_P(object);
		fcc.object = Z_OBJ_P(object);

		if (zend_call_function(&fci, &fcc) == FAILURE) {
			php_error_docref(NULL, E_WARNING, "Could not execute %s::%s()", ZSTR_VAL(uwrap->ce->name), ZSTR_VAL(uwrap->ce->constructor->common.function_name));
			zval_ptr_dtor(object);
			ZVAL_UNDEF(object);
		} else {
			zval_ptr_dtor(&retval);
		}
	}
}