#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_7__ ;
typedef  struct TYPE_17__   TYPE_6__ ;
typedef  struct TYPE_16__   TYPE_5__ ;
typedef  struct TYPE_15__   TYPE_4__ ;
typedef  struct TYPE_14__   TYPE_3__ ;
typedef  struct TYPE_13__   TYPE_2__ ;
typedef  struct TYPE_12__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zval ;
struct TYPE_14__ {int /*<<< orphan*/  function_name; } ;
struct TYPE_15__ {TYPE_3__ common; } ;
typedef  TYPE_4__ zend_function ;
struct TYPE_16__ {int /*<<< orphan*/ * object; int /*<<< orphan*/ * called_scope; TYPE_4__* function_handler; } ;
typedef  TYPE_5__ zend_fcall_info_cache ;
struct TYPE_17__ {int size; int param_count; int no_separation; int /*<<< orphan*/  function_name; int /*<<< orphan*/ * params; int /*<<< orphan*/ * retval; int /*<<< orphan*/ * object; } ;
typedef  TYPE_6__ zend_fcall_info ;
struct TYPE_12__ {int /*<<< orphan*/  zresource; } ;
struct TYPE_13__ {TYPE_1__ file; } ;
struct TYPE_18__ {TYPE_2__ u; } ;
typedef  TYPE_7__ spl_filesystem_object ;
typedef  int /*<<< orphan*/  fci ;

/* Variables and functions */
 int FAILURE ; 
 int /*<<< orphan*/  RETVAL_FALSE ; 
 scalar_t__ SUCCESS ; 
 int /*<<< orphan*/  WRONG_PARAM_COUNT_WITH_RETVAL (int) ; 
 int /*<<< orphan*/  ZVAL_STR (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZVAL_UNDEF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZVAL_ZVAL (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ Z_ISUNDEF (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  efree (int /*<<< orphan*/ *) ; 
 scalar_t__ safe_emalloc (int,int,int /*<<< orphan*/ ) ; 
 int zend_call_function (TYPE_6__*,TYPE_5__*) ; 
 scalar_t__ zend_get_parameters_array_ex (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int spl_filesystem_file_call(spl_filesystem_object *intern, zend_function *func_ptr, int pass_num_args, zval *return_value, zval *arg2) /* {{{ */
{
	zend_fcall_info fci;
	zend_fcall_info_cache fcic;
	zval *zresource_ptr = &intern->u.file.zresource, retval;
	int result;
	int num_args = pass_num_args + (arg2 ? 2 : 1);

	zval *params = (zval*)safe_emalloc(num_args, sizeof(zval), 0);

	params[0] = *zresource_ptr;

	if (arg2) {
		params[1] = *arg2;
	}

	if (zend_get_parameters_array_ex(pass_num_args, params + (arg2 ? 2 : 1)) != SUCCESS) {
		efree(params);
		WRONG_PARAM_COUNT_WITH_RETVAL(FAILURE);
	}

	ZVAL_UNDEF(&retval);

	fci.size = sizeof(fci);
	fci.object = NULL;
	fci.retval = &retval;
	fci.param_count = num_args;
	fci.params = params;
	fci.no_separation = 1;
	ZVAL_STR(&fci.function_name, func_ptr->common.function_name);

	fcic.function_handler = func_ptr;
	fcic.called_scope = NULL;
	fcic.object = NULL;

	result = zend_call_function(&fci, &fcic);

	if (result == FAILURE || Z_ISUNDEF(retval)) {
		RETVAL_FALSE;
	} else {
		ZVAL_ZVAL(return_value, &retval, 0, 0);
	}

	efree(params);
	return result;
}