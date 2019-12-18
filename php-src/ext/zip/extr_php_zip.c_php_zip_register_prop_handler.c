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
typedef  int /*<<< orphan*/  zval ;
typedef  int /*<<< orphan*/  zip_read_int_t ;
typedef  int /*<<< orphan*/  zip_read_const_char_t ;
typedef  int /*<<< orphan*/  zip_read_const_char_from_ze_t ;
struct TYPE_3__ {int type; int /*<<< orphan*/  read_const_char_from_obj_func; int /*<<< orphan*/  read_int_func; int /*<<< orphan*/  read_const_char_func; } ;
typedef  TYPE_1__ zip_prop_handler ;
typedef  int /*<<< orphan*/  zend_string ;
typedef  int /*<<< orphan*/  HashTable ;

/* Variables and functions */
 int /*<<< orphan*/  ZEND_ACC_PUBLIC ; 
 int /*<<< orphan*/  ZVAL_NULL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strlen (char*) ; 
 int /*<<< orphan*/  zend_declare_property_ex (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zend_hash_add_mem (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*,int) ; 
 int /*<<< orphan*/ * zend_string_init_interned (char*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  zend_string_release_ex (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  zip_class_entry ; 

__attribute__((used)) static void php_zip_register_prop_handler(HashTable *prop_handler, char *name, zip_read_int_t read_int_func, zip_read_const_char_t read_char_func, zip_read_const_char_from_ze_t read_char_from_obj_func, int rettype) /* {{{ */
{
	zip_prop_handler hnd;
	zend_string *str;
	zval tmp;

	hnd.read_const_char_func = read_char_func;
	hnd.read_int_func = read_int_func;
	hnd.read_const_char_from_obj_func = read_char_from_obj_func;
	hnd.type = rettype;
	str = zend_string_init_interned(name, strlen(name), 1);
	zend_hash_add_mem(prop_handler, str, &hnd, sizeof(zip_prop_handler));

	/* Register for reflection */
	ZVAL_NULL(&tmp);
	zend_declare_property_ex(zip_class_entry, str, &tmp, ZEND_ACC_PUBLIC, NULL);
	zend_string_release_ex(str, 1);
}