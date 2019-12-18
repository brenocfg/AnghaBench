#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zval ;
typedef  int /*<<< orphan*/  zend_string ;
struct TYPE_4__ {int flags; int /*<<< orphan*/ * ce; } ;
typedef  TYPE_1__ zend_property_info ;
typedef  int /*<<< orphan*/  zend_class_entry ;

/* Variables and functions */
 int ZEND_ACC_PRIVATE ; 
 int /*<<< orphan*/  add_next_index_zval (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reflection_property_factory (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void _addproperty(zend_property_info *pptr, zend_string *key, zend_class_entry *ce, zval *retval, long filter)
{
	if ((pptr->flags & ZEND_ACC_PRIVATE) && pptr->ce != ce) {
		return;
	}

	if (pptr->flags	& filter) {
		zval property;
		reflection_property_factory(ce, key, pptr, &property);
		add_next_index_zval(retval, &property);
	}
}