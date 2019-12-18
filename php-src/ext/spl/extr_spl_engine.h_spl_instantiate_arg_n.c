#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_14__   TYPE_5__ ;
typedef  struct TYPE_13__   TYPE_4__ ;
typedef  struct TYPE_12__   TYPE_3__ ;
typedef  struct TYPE_11__   TYPE_2__ ;
typedef  struct TYPE_10__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zval ;
struct TYPE_10__ {int /*<<< orphan*/  function_name; } ;
struct TYPE_11__ {TYPE_1__ common; } ;
typedef  TYPE_2__ zend_function ;
struct TYPE_12__ {void* object; TYPE_5__* called_scope; TYPE_2__* function_handler; } ;
typedef  TYPE_3__ zend_fcall_info_cache ;
struct TYPE_13__ {int size; int param_count; int no_separation; int /*<<< orphan*/ * params; int /*<<< orphan*/ * retval; void* object; int /*<<< orphan*/  function_name; } ;
typedef  TYPE_4__ zend_fcall_info ;
struct TYPE_14__ {TYPE_2__* constructor; } ;
typedef  TYPE_5__ zend_class_entry ;

/* Variables and functions */
 int /*<<< orphan*/  ZVAL_STR (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 void* Z_OBJ_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spl_instantiate (TYPE_5__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zend_call_function (TYPE_4__*,TYPE_3__*) ; 

__attribute__((used)) static inline void spl_instantiate_arg_n(zend_class_entry *pce, zval *retval, int argc, zval *argv)
{
	zend_function *func = pce->constructor;
	zend_fcall_info fci;
	zend_fcall_info_cache fcc;
	zval dummy;

	spl_instantiate(pce, retval);

	fci.size = sizeof(zend_fcall_info);
	ZVAL_STR(&fci.function_name, func->common.function_name);
	fci.object = Z_OBJ_P(retval);
	fci.retval = &dummy;
	fci.param_count = argc;
	fci.params = argv;
	fci.no_separation = 1;

	fcc.function_handler = func;
	fcc.called_scope = pce;
	fcc.object = Z_OBJ_P(retval);

	zend_call_function(&fci, &fcc);
}