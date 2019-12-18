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
typedef  int /*<<< orphan*/  zend_string ;
struct _zend_module_entry {int /*<<< orphan*/  name; } ;
struct TYPE_3__ {int /*<<< orphan*/ * ce; int /*<<< orphan*/  ref_type; struct _zend_module_entry* ptr; } ;
typedef  TYPE_1__ reflection_object ;

/* Variables and functions */
 int /*<<< orphan*/  REF_TYPE_OTHER ; 
 int /*<<< orphan*/  ZSTR_VAL (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ZVAL_STRINGL (int /*<<< orphan*/ ,int /*<<< orphan*/ ,size_t) ; 
 TYPE_1__* Z_REFLECTION_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  module_registry ; 
 int /*<<< orphan*/  reflection_extension_ptr ; 
 int /*<<< orphan*/  reflection_instantiate (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reflection_prop_name (int /*<<< orphan*/ *) ; 
 size_t strlen (char const*) ; 
 struct _zend_module_entry* zend_hash_find_ptr (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zend_str_tolower_copy (int /*<<< orphan*/ ,char const*,size_t) ; 
 int /*<<< orphan*/ * zend_string_alloc (size_t,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zend_string_efree (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void reflection_extension_factory(zval *object, const char *name_str)
{
	reflection_object *intern;
	size_t name_len = strlen(name_str);
	zend_string *lcname;
	struct _zend_module_entry *module;

	lcname = zend_string_alloc(name_len, 0);
	zend_str_tolower_copy(ZSTR_VAL(lcname), name_str, name_len);
	module = zend_hash_find_ptr(&module_registry, lcname);
	zend_string_efree(lcname);
	if (!module) {
		return;
	}

	reflection_instantiate(reflection_extension_ptr, object);
	intern = Z_REFLECTION_P(object);
	intern->ptr = module;
	intern->ref_type = REF_TYPE_OTHER;
	intern->ce = NULL;
	ZVAL_STRINGL(reflection_prop_name(object), module->name, name_len);
}