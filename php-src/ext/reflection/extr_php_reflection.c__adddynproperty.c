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
typedef  int /*<<< orphan*/  zend_string ;
typedef  int /*<<< orphan*/  zend_class_entry ;

/* Variables and functions */
 scalar_t__ IS_INDIRECT ; 
 scalar_t__ Z_TYPE_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  add_next_index_zval (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reflection_property_factory (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void _adddynproperty(zval *ptr, zend_string *key, zend_class_entry *ce, zval *retval)
{
	zval property;

	/* under some circumstances, the properties hash table may contain numeric
	 * properties (e.g. when casting from array). This is a WON'T FIX bug, at
	 * least for the moment. Ignore these */
	if (key == NULL) {
		return;
	}

	/* Not a dynamic property */
	if (Z_TYPE_P(ptr) == IS_INDIRECT) {
		return;
	}

	reflection_property_factory(ce, key, NULL, &property);
	add_next_index_zval(retval, &property);
}