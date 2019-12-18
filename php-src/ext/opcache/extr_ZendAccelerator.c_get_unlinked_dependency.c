#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_3__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zend_string ;
struct TYPE_9__ {int ce_flags; size_t num_interfaces; size_t num_traits; TYPE_2__* trait_names; TYPE_1__* interface_names; scalar_t__ parent_name; } ;
typedef  TYPE_3__ zend_class_entry ;
typedef  size_t uint32_t ;
struct TYPE_8__ {scalar_t__ name; int /*<<< orphan*/ * lc_name; } ;
struct TYPE_7__ {scalar_t__ name; int /*<<< orphan*/ * lc_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  EG (int /*<<< orphan*/ ) ; 
 int ZEND_ACC_CONSTANTS_UPDATED ; 
 int ZEND_ACC_PROPERTY_TYPES_RESOLVED ; 
 char* ZSTR_VAL (scalar_t__) ; 
 int /*<<< orphan*/  class_table ; 
 int /*<<< orphan*/  preload_needed_types_known (TYPE_3__*) ; 
 TYPE_3__* zend_hash_find_ptr (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zend_string_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * zend_string_tolower (scalar_t__) ; 

__attribute__((used)) static void get_unlinked_dependency(zend_class_entry *ce, const char **kind, const char **name) {
	zend_class_entry *p;
	*kind = "Unknown reason";
	*name = "";

	if (ce->parent_name) {
		zend_string *key = zend_string_tolower(ce->parent_name);
		p = zend_hash_find_ptr(EG(class_table), key);
		zend_string_release(key);
		if (!p) {
			*kind = "Unknown parent ";
			*name = ZSTR_VAL(ce->parent_name);
			return;
		}
		if (!(p->ce_flags & ZEND_ACC_CONSTANTS_UPDATED)) {
			*kind = "Parent with unresolved initializers ";
			*name = ZSTR_VAL(ce->parent_name);
			return;
		}
		if (!(p->ce_flags & ZEND_ACC_PROPERTY_TYPES_RESOLVED)) {
			*kind = "Parent with unresolved property types ";
			*name = ZSTR_VAL(ce->parent_name);
			return;
		}
	}

	if (ce->num_interfaces) {
		uint32_t i;
		for (i = 0; i < ce->num_interfaces; i++) {
			p = zend_hash_find_ptr(EG(class_table), ce->interface_names[i].lc_name);
			if (!p) {
				*kind = "Unknown interface ";
				*name = ZSTR_VAL(ce->interface_names[i].name);
				return;
			}
		}
	}

	if (ce->num_traits) {
		uint32_t i;
		for (i = 0; i < ce->num_traits; i++) {
			p = zend_hash_find_ptr(EG(class_table), ce->trait_names[i].lc_name);
			if (!p) {
				*kind = "Unknown trait ";
				*name = ZSTR_VAL(ce->trait_names[i].name);
				return;
			}
		}
	}

	if (!preload_needed_types_known(ce)) {
		*kind = "Unknown type dependencies";
		return;
	}
}