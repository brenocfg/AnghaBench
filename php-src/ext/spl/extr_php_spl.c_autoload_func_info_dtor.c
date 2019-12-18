#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zval ;
struct TYPE_6__ {int /*<<< orphan*/  closure; TYPE_3__* func_ptr; int /*<<< orphan*/  obj; } ;
typedef  TYPE_2__ autoload_func_info ;
struct TYPE_5__ {int fn_flags; int /*<<< orphan*/  function_name; } ;
struct TYPE_7__ {TYPE_1__ common; } ;

/* Variables and functions */
 scalar_t__ UNEXPECTED (int) ; 
 int ZEND_ACC_CALL_VIA_TRAMPOLINE ; 
 int /*<<< orphan*/  Z_ISUNDEF (int /*<<< orphan*/ ) ; 
 scalar_t__ Z_PTR_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  efree (TYPE_2__*) ; 
 int /*<<< orphan*/  zend_free_trampoline (TYPE_3__*) ; 
 int /*<<< orphan*/  zend_string_release_ex (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zval_ptr_dtor (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void autoload_func_info_dtor(zval *element)
{
	autoload_func_info *alfi = (autoload_func_info*)Z_PTR_P(element);
	if (!Z_ISUNDEF(alfi->obj)) {
		zval_ptr_dtor(&alfi->obj);
	}
	if (alfi->func_ptr &&
		UNEXPECTED(alfi->func_ptr->common.fn_flags & ZEND_ACC_CALL_VIA_TRAMPOLINE)) {
		zend_string_release_ex(alfi->func_ptr->common.function_name, 0);
		zend_free_trampoline(alfi->func_ptr);
	}
	if (!Z_ISUNDEF(alfi->closure)) {
		zval_ptr_dtor(&alfi->closure);
	}
	efree(alfi);
}