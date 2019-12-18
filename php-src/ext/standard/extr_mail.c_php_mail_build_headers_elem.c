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
 int /*<<< orphan*/  E_WARNING ; 
#define  IS_ARRAY 129 
#define  IS_STRING 128 
 int /*<<< orphan*/  SUCCESS ; 
 int /*<<< orphan*/  ZSTR_VAL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Z_STRVAL_P (int /*<<< orphan*/ *) ; 
 int Z_TYPE_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  php_error_docref (int /*<<< orphan*/ *,int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  php_mail_build_headers_check_field_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  php_mail_build_headers_check_field_value (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  php_mail_build_headers_elems (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smart_str_append (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  smart_str_appendl (int /*<<< orphan*/ *,char*,int) ; 
 int /*<<< orphan*/  smart_str_appends (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void php_mail_build_headers_elem(smart_str *s, zend_string *key, zval *val)
{
	switch(Z_TYPE_P(val)) {
		case IS_STRING:
			if (php_mail_build_headers_check_field_name(key) != SUCCESS) {
				php_error_docref(NULL, E_WARNING, "Header field name (%s) contains invalid chars", ZSTR_VAL(key));
				return;
			}
			if (php_mail_build_headers_check_field_value(val) != SUCCESS) {
				php_error_docref(NULL, E_WARNING, "Header field value (%s => %s) contains invalid chars or format", ZSTR_VAL(key), Z_STRVAL_P(val));
				return;
			}
			smart_str_append(s, key);
			smart_str_appendl(s, ": ", 2);
			smart_str_appends(s, Z_STRVAL_P(val));
			smart_str_appendl(s, "\r\n", 2);
			break;
		case IS_ARRAY:
			php_mail_build_headers_elems(s, key, val);
			break;
		default:
			php_error_docref(NULL, E_WARNING, "headers array elements must be string or array (%s)", ZSTR_VAL(key));
	}
}