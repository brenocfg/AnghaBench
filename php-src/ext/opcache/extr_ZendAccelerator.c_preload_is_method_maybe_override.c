#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zend_string ;
struct TYPE_8__ {size_t num_interfaces; size_t num_traits; int /*<<< orphan*/  function_table; TYPE_2__* trait_names; TYPE_1__* interface_names; scalar_t__ parent_name; scalar_t__ trait_precedences; scalar_t__ trait_aliases; } ;
typedef  TYPE_3__ zend_class_entry ;
typedef  int zend_bool ;
typedef  size_t uint32_t ;
struct TYPE_7__ {int /*<<< orphan*/ * lc_name; } ;
struct TYPE_6__ {int /*<<< orphan*/ * lc_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  EG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  class_table ; 
 scalar_t__ zend_hash_exists (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_3__* zend_hash_find_ptr (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zend_string_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * zend_string_tolower (scalar_t__) ; 

__attribute__((used)) static zend_bool preload_is_method_maybe_override(zend_class_entry *ce, zend_string *lcname) {
	zend_class_entry *p;
	if (ce->trait_aliases || ce->trait_precedences) {
		return 1;
	}

	if (ce->parent_name) {
		zend_string *key = zend_string_tolower(ce->parent_name);
		p = zend_hash_find_ptr(EG(class_table), key);
		zend_string_release(key);
		if (zend_hash_exists(&p->function_table, lcname)) {
			return 1;
		}
	}

	if (ce->num_interfaces) {
		uint32_t i;
		for (i = 0; i < ce->num_interfaces; i++) {
			zend_class_entry *p = zend_hash_find_ptr(EG(class_table), ce->interface_names[i].lc_name);
			if (zend_hash_exists(&p->function_table, lcname)) {
				return 1;
			}
		}
	}

	if (ce->num_traits) {
		uint32_t i;
		for (i = 0; i < ce->num_traits; i++) {
			zend_class_entry *p = zend_hash_find_ptr(EG(class_table), ce->trait_names[i].lc_name);
			if (zend_hash_exists(&p->function_table, lcname)) {
				return 1;
			}
		}
	}

	return 0;
}