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
typedef  int /*<<< orphan*/  zend_string ;
struct TYPE_3__ {int /*<<< orphan*/  value; int /*<<< orphan*/  ce; } ;
typedef  TYPE_1__ zend_class_constant ;
typedef  int /*<<< orphan*/  smart_str ;

/* Variables and functions */
 scalar_t__ IS_ARRAY ; 
 int /*<<< orphan*/  ZSTR_VAL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Z_ACCESS_FLAGS (int /*<<< orphan*/ ) ; 
 scalar_t__ Z_TYPE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smart_str_append_printf (int /*<<< orphan*/ *,char*,char*,char*,char const*,char*,...) ; 
 int /*<<< orphan*/  zend_tmp_string_release (int /*<<< orphan*/ *) ; 
 char* zend_visibility_string (int /*<<< orphan*/ ) ; 
 char* zend_zval_type_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * zval_get_tmp_string (int /*<<< orphan*/ *,int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  zval_update_constant_ex (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void _class_const_string(smart_str *str, char *name, zend_class_constant *c, char *indent)
{
	char *visibility = zend_visibility_string(Z_ACCESS_FLAGS(c->value));
	const char *type;

	zval_update_constant_ex(&c->value, c->ce);
	type = zend_zval_type_name(&c->value);

	if (Z_TYPE(c->value) == IS_ARRAY) {
		smart_str_append_printf(str, "%sConstant [ %s %s %s ] { Array }\n",
						indent, visibility, type, name);
	} else {
		zend_string *tmp_value_str;
		zend_string *value_str = zval_get_tmp_string(&c->value, &tmp_value_str);

		smart_str_append_printf(str, "%sConstant [ %s %s %s ] { %s }\n",
						indent, visibility, type, name, ZSTR_VAL(value_str));

		zend_tmp_string_release(tmp_value_str);
	}
}