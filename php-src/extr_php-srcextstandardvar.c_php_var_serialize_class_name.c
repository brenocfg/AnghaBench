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
typedef  int /*<<< orphan*/  zend_bool ;
typedef  int /*<<< orphan*/  smart_str ;

/* Variables and functions */
 int /*<<< orphan*/  PHP_CLASS_ATTRIBUTES ; 
 int /*<<< orphan*/  PHP_CLEANUP_CLASS_ATTRIBUTES () ; 
 int /*<<< orphan*/  PHP_SET_CLASS_ATTRIBUTES (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZSTR_LEN (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  class_name ; 
 int /*<<< orphan*/  incomplete_class ; 
 int /*<<< orphan*/  smart_str_append (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smart_str_append_unsigned (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  smart_str_appendl (int /*<<< orphan*/ *,char*,int) ; 

__attribute__((used)) static inline zend_bool php_var_serialize_class_name(smart_str *buf, zval *struc) /* {{{ */
{
	PHP_CLASS_ATTRIBUTES;

	PHP_SET_CLASS_ATTRIBUTES(struc);
	smart_str_appendl(buf, "O:", 2);
	smart_str_append_unsigned(buf, ZSTR_LEN(class_name));
	smart_str_appendl(buf, ":\"", 2);
	smart_str_append(buf, class_name);
	smart_str_appendl(buf, "\":", 2);
	PHP_CLEANUP_CLASS_ATTRIBUTES();
	return incomplete_class;
}