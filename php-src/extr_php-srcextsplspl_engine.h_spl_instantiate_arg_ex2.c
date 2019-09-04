#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_3__ ;
typedef  struct TYPE_9__   TYPE_2__ ;
typedef  struct TYPE_8__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zval ;
struct TYPE_8__ {int /*<<< orphan*/  function_name; } ;
struct TYPE_9__ {TYPE_1__ common; } ;
typedef  TYPE_2__ zend_function ;
struct TYPE_10__ {TYPE_2__* constructor; } ;
typedef  TYPE_3__ zend_class_entry ;

/* Variables and functions */
 int /*<<< orphan*/  ZSTR_LEN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ZSTR_VAL (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  Z_OBJ_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spl_instantiate (TYPE_3__*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zend_call_method (int /*<<< orphan*/ ,TYPE_3__*,TYPE_2__**,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int spl_instantiate_arg_ex2(zend_class_entry *pce, zval *retval, zval *arg1, zval *arg2)
{
	zend_function *func = pce->constructor;
	spl_instantiate(pce, retval);

	zend_call_method(Z_OBJ_P(retval), pce, &func, ZSTR_VAL(func->common.function_name), ZSTR_LEN(func->common.function_name), NULL, 2, arg1, arg2);
	return 0;
}