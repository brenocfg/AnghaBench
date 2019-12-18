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
typedef  int /*<<< orphan*/  smart_str ;

/* Variables and functions */
 scalar_t__ IS_ARRAY ; 
 scalar_t__ IS_STRING ; 
 int /*<<< orphan*/  ZSTR_VAL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Z_STRVAL_P (int /*<<< orphan*/ *) ; 
 scalar_t__ Z_TYPE_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smart_str_append_printf (int /*<<< orphan*/ *,char*,char*,char const*,char*,...) ; 
 int /*<<< orphan*/  zend_tmp_string_release (int /*<<< orphan*/ *) ; 
 char* zend_zval_type_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * zval_get_tmp_string (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 

__attribute__((used)) static void _const_string(smart_str *str, char *name, zval *value, char *indent)
{
	const char *type = zend_zval_type_name(value);

	if (Z_TYPE_P(value) == IS_ARRAY) {
		smart_str_append_printf(str, "%s    Constant [ %s %s ] { Array }\n",
						indent, type, name);
	} else if (Z_TYPE_P(value) == IS_STRING) {
		smart_str_append_printf(str, "%s    Constant [ %s %s ] { %s }\n",
						indent, type, name, Z_STRVAL_P(value));
	} else {
		zend_string *tmp_value_str;
		zend_string *value_str = zval_get_tmp_string(value, &tmp_value_str);
		smart_str_append_printf(str, "%s    Constant [ %s %s ] { %s }\n",
						indent, type, name, ZSTR_VAL(value_str));
		zend_tmp_string_release(tmp_value_str);
	}
}