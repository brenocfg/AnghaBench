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
typedef  int /*<<< orphan*/  HashTable ;

/* Variables and functions */
 int /*<<< orphan*/  ZVAL_STRING (int /*<<< orphan*/ *,char*) ; 
 char* getenv (char*) ; 
 int /*<<< orphan*/  zend_hash_str_del (int /*<<< orphan*/ *,char*,int) ; 
 scalar_t__ zend_hash_str_exists (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  zend_hash_str_update (int /*<<< orphan*/ *,char*,int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void check_http_proxy(HashTable *var_table)
{
	if (zend_hash_str_exists(var_table, "HTTP_PROXY", sizeof("HTTP_PROXY")-1)) {
		char *local_proxy = getenv("HTTP_PROXY");

		if (!local_proxy) {
			zend_hash_str_del(var_table, "HTTP_PROXY", sizeof("HTTP_PROXY")-1);
		} else {
			zval local_zval;
			ZVAL_STRING(&local_zval, local_proxy);
			zend_hash_str_update(var_table, "HTTP_PROXY", sizeof("HTTP_PROXY")-1, &local_zval);
		}
	}
}