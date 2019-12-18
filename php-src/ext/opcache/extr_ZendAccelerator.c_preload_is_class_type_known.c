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
struct TYPE_3__ {int /*<<< orphan*/  name; } ;
typedef  TYPE_1__ zend_class_entry ;
typedef  int zend_bool ;

/* Variables and functions */
 int /*<<< orphan*/  EG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  class_table ; 
 int zend_hash_exists (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ zend_string_equals_ci (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ zend_string_equals_literal_ci (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/  zend_string_release (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * zend_string_tolower (int /*<<< orphan*/ *) ; 

__attribute__((used)) static zend_bool preload_is_class_type_known(zend_class_entry *ce, zend_string *name) {
	if (zend_string_equals_literal_ci(name, "self") ||
		zend_string_equals_literal_ci(name, "parent") ||
		zend_string_equals_ci(name, ce->name)) {
		return 1;
	}

	zend_string *lcname = zend_string_tolower(name);
	zend_bool known = zend_hash_exists(EG(class_table), lcname);
	zend_string_release(lcname);
	return known;
}