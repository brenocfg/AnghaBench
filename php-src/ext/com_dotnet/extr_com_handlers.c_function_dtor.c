#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zval ;
struct TYPE_3__ {struct TYPE_3__* arg_info; int /*<<< orphan*/  function_name; } ;
typedef  TYPE_1__ zend_internal_function ;

/* Variables and functions */
 scalar_t__ Z_PTR_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  efree (TYPE_1__*) ; 
 int /*<<< orphan*/  zend_string_release_ex (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void function_dtor(zval *zv)
{
	zend_internal_function *f = (zend_internal_function*)Z_PTR_P(zv);

	zend_string_release_ex(f->function_name, 0);
	if (f->arg_info) {
		efree(f->arg_info);
	}
	efree(f);
}