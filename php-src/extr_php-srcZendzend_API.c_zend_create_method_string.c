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
typedef  int /*<<< orphan*/  zend_string ;

/* Variables and functions */
 int ZSTR_LEN (int /*<<< orphan*/ *) ; 
 char* ZSTR_VAL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int /*<<< orphan*/ * zend_string_alloc (int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static zend_string *zend_create_method_string(zend_string *class_name, zend_string *method_name) {
	zend_string *callable_name = zend_string_alloc(
		ZSTR_LEN(class_name) + ZSTR_LEN(method_name) + sizeof("::") - 1, 0);
	char *ptr = ZSTR_VAL(callable_name);
	memcpy(ptr, ZSTR_VAL(class_name), ZSTR_LEN(class_name));
	ptr += ZSTR_LEN(class_name);
	memcpy(ptr, "::", sizeof("::") - 1);
	ptr += sizeof("::") - 1;
	memcpy(ptr, ZSTR_VAL(method_name), ZSTR_LEN(method_name) + 1);
	return callable_name;
}