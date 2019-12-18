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
typedef  int /*<<< orphan*/  php_password_algo ;

/* Variables and functions */
 int /*<<< orphan*/  php_password_algo_default () ; 
 int /*<<< orphan*/  const* php_password_algo_find_zval_ex (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static const php_password_algo* php_password_algo_find_zval(zval *arg) {
	return php_password_algo_find_zval_ex(arg, php_password_algo_default());
}