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

/* Variables and functions */
 int /*<<< orphan*/  php_password_algos ; 
 int /*<<< orphan*/  strlen (char const*) ; 
 int /*<<< orphan*/  zend_hash_str_del (int /*<<< orphan*/ *,char const*,int /*<<< orphan*/ ) ; 

void php_password_algo_unregister(const char *ident) {
	zend_hash_str_del(&php_password_algos, ident, strlen(ident));
}