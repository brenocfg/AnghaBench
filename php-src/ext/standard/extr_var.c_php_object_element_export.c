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
typedef  scalar_t__ zend_ulong ;
typedef  int /*<<< orphan*/  zend_string ;
typedef  int /*<<< orphan*/  zend_long ;
typedef  int /*<<< orphan*/  smart_str ;

/* Variables and functions */
 int /*<<< orphan*/  buffer_append_spaces (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * php_addcslashes_str (char const*,size_t,char*,int) ; 
 int /*<<< orphan*/  php_var_export_ex (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smart_str_append (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smart_str_append_long (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smart_str_appendc (int /*<<< orphan*/ *,char) ; 
 int /*<<< orphan*/  smart_str_appendl (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  zend_string_release_ex (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zend_unmangle_property_name_ex (int /*<<< orphan*/ *,char const**,char const**,size_t*) ; 

__attribute__((used)) static void php_object_element_export(zval *zv, zend_ulong index, zend_string *key, int level, smart_str *buf) /* {{{ */
{
	buffer_append_spaces(buf, level + 2);
	if (key != NULL) {
		const char *class_name, *prop_name;
		size_t prop_name_len;
		zend_string *pname_esc;

		zend_unmangle_property_name_ex(key, &class_name, &prop_name, &prop_name_len);
		pname_esc = php_addcslashes_str(prop_name, prop_name_len, "'\\", 2);

		smart_str_appendc(buf, '\'');
		smart_str_append(buf, pname_esc);
		smart_str_appendc(buf, '\'');
		zend_string_release_ex(pname_esc, 0);
	} else {
		smart_str_append_long(buf, (zend_long) index);
	}
	smart_str_appendl(buf, " => ", 4);
	php_var_export_ex(zv, level + 2, buf);
	smart_str_appendc(buf, ',');
	smart_str_appendc(buf, '\n');
}