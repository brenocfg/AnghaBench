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
 int /*<<< orphan*/  ZSTR_LEN (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZSTR_VAL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  buffer_append_spaces (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * php_addcslashes (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/ * php_str_to_str (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*,int,char*,int) ; 
 int /*<<< orphan*/  php_var_export_ex (int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smart_str_append (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smart_str_append_long (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smart_str_appendc (int /*<<< orphan*/ *,char) ; 
 int /*<<< orphan*/  smart_str_appendl (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  zend_string_free (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void php_array_element_export(zval *zv, zend_ulong index, zend_string *key, int level, smart_str *buf) /* {{{ */
{
	if (key == NULL) { /* numeric key */
		buffer_append_spaces(buf, level+1);
		smart_str_append_long(buf, (zend_long) index);
		smart_str_appendl(buf, " => ", 4);

	} else { /* string key */
		zend_string *tmp_str;
		zend_string *ckey = php_addcslashes(key, "'\\", 2);
		tmp_str = php_str_to_str(ZSTR_VAL(ckey), ZSTR_LEN(ckey), "\0", 1, "' . \"\\0\" . '", 12);

		buffer_append_spaces(buf, level + 1);

		smart_str_appendc(buf, '\'');
		smart_str_append(buf, tmp_str);
		smart_str_appendl(buf, "' => ", 5);

		zend_string_free(ckey);
		zend_string_free(tmp_str);
	}
	php_var_export_ex(zv, level + 2, buf);

	smart_str_appendc(buf, ',');
	smart_str_appendc(buf, '\n');
}