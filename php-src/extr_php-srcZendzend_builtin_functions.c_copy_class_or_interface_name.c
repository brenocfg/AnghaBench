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
struct TYPE_3__ {int refcount; int ce_flags; int /*<<< orphan*/ * name; } ;
typedef  TYPE_1__ zend_class_entry ;

/* Variables and functions */
 int ZEND_ACC_IMMUTABLE ; 
 int /*<<< orphan*/  add_next_index_str (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ same_name (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zend_string_copy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void copy_class_or_interface_name(zval *array, zend_string *key, zend_class_entry *ce) /* {{{ */
{
	if ((ce->refcount == 1 && !(ce->ce_flags & ZEND_ACC_IMMUTABLE)) ||
		same_name(key, ce->name)) {
		key = ce->name;
	}
	add_next_index_str(array, zend_string_copy(key));
}