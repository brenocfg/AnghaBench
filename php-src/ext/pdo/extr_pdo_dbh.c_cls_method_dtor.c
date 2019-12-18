#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zval ;
struct TYPE_4__ {scalar_t__ function_name; } ;
struct TYPE_5__ {TYPE_1__ common; } ;
typedef  TYPE_2__ zend_function ;

/* Variables and functions */
 scalar_t__ Z_PTR_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  efree (TYPE_2__*) ; 
 int /*<<< orphan*/  zend_string_release_ex (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cls_method_dtor(zval *el) /* {{{ */ {
	zend_function *func = (zend_function*)Z_PTR_P(el);
	if (func->common.function_name) {
		zend_string_release_ex(func->common.function_name, 0);
	}
	efree(func);
}