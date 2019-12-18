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
typedef  int /*<<< orphan*/  zend_string ;

/* Variables and functions */
 int /*<<< orphan*/  GC_MAKE_PERSISTENT_LOCAL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZVAL_NEW_STR (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * Z_STR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fcgi_mgmt_vars ; 
 int /*<<< orphan*/  zend_hash_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * zend_string_init (char const*,size_t,int) ; 
 int /*<<< orphan*/  zend_string_release_ex (int /*<<< orphan*/ *,int) ; 

void fcgi_set_mgmt_var(const char * name, size_t name_len, const char * value, size_t value_len)
{
	zval zvalue;
	zend_string *key = zend_string_init(name, name_len, 1);
	ZVAL_NEW_STR(&zvalue, zend_string_init(value, value_len, 1));
	GC_MAKE_PERSISTENT_LOCAL(key);
	GC_MAKE_PERSISTENT_LOCAL(Z_STR(zvalue));
	zend_hash_add(&fcgi_mgmt_vars, key, &zvalue);
	zend_string_release_ex(key, 1);
}