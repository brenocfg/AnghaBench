#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  zval ;
struct php_sqlite3_bound_param {int /*<<< orphan*/  parameter; scalar_t__ name; } ;

/* Variables and functions */
 int /*<<< orphan*/  ZVAL_UNDEF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Z_ISNULL (int /*<<< orphan*/ ) ; 
 scalar_t__ Z_PTR_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  efree (struct php_sqlite3_bound_param*) ; 
 int /*<<< orphan*/  zend_string_release_ex (scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zval_ptr_dtor (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void sqlite3_param_dtor(zval *data) /* {{{ */
{
	struct php_sqlite3_bound_param *param = (struct php_sqlite3_bound_param*)Z_PTR_P(data);

	if (param->name) {
		zend_string_release_ex(param->name, 0);
	}

	if (!Z_ISNULL(param->parameter)) {
		zval_ptr_dtor(&(param->parameter));
		ZVAL_UNDEF(&param->parameter);
	}
	efree(param);
}