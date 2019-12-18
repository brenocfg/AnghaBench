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
struct TYPE_3__ {int /*<<< orphan*/  li_read; int /*<<< orphan*/ * hash_key; } ;
typedef  TYPE_1__ MY_MYSQL ;

/* Variables and functions */
 int /*<<< orphan*/  ZVAL_UNDEF (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Z_ISUNDEF (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zend_string_release_ex (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zval_ptr_dtor (int /*<<< orphan*/ *) ; 

void php_clear_mysql(MY_MYSQL *mysql) {
	if (mysql->hash_key) {
		zend_string_release_ex(mysql->hash_key, 0);
		mysql->hash_key = NULL;
	}
	if (!Z_ISUNDEF(mysql->li_read)) {
		zval_ptr_dtor(&(mysql->li_read));
		ZVAL_UNDEF(&mysql->li_read);
	}
}