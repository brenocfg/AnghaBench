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
 int /*<<< orphan*/  PG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  auto_globals_jit ; 
 int /*<<< orphan*/  php_auto_globals_create_cookie ; 
 int /*<<< orphan*/  php_auto_globals_create_env ; 
 int /*<<< orphan*/  php_auto_globals_create_files ; 
 int /*<<< orphan*/  php_auto_globals_create_get ; 
 int /*<<< orphan*/  php_auto_globals_create_post ; 
 int /*<<< orphan*/  php_auto_globals_create_request ; 
 int /*<<< orphan*/  php_auto_globals_create_server ; 
 int /*<<< orphan*/  zend_register_auto_global (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zend_string_init_interned (char*,int,int) ; 

void php_startup_auto_globals(void)
{
	zend_register_auto_global(zend_string_init_interned("_GET", sizeof("_GET")-1, 1), 0, php_auto_globals_create_get);
	zend_register_auto_global(zend_string_init_interned("_POST", sizeof("_POST")-1, 1), 0, php_auto_globals_create_post);
	zend_register_auto_global(zend_string_init_interned("_COOKIE", sizeof("_COOKIE")-1, 1), 0, php_auto_globals_create_cookie);
	zend_register_auto_global(zend_string_init_interned("_SERVER", sizeof("_SERVER")-1, 1), PG(auto_globals_jit), php_auto_globals_create_server);
	zend_register_auto_global(zend_string_init_interned("_ENV", sizeof("_ENV")-1, 1), PG(auto_globals_jit), php_auto_globals_create_env);
	zend_register_auto_global(zend_string_init_interned("_REQUEST", sizeof("_REQUEST")-1, 1), PG(auto_globals_jit), php_auto_globals_create_request);
	zend_register_auto_global(zend_string_init_interned("_FILES", sizeof("_FILES")-1, 1), 0, php_auto_globals_create_files);
}