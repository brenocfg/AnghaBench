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
struct TYPE_3__ {int offset; int /*<<< orphan*/ * ce; int /*<<< orphan*/ * name; int /*<<< orphan*/  flags; int /*<<< orphan*/ * doc_comment; } ;
typedef  TYPE_1__ zend_property_info ;
typedef  int /*<<< orphan*/  zend_class_entry ;

/* Variables and functions */
 scalar_t__ IS_INDIRECT ; 
 int /*<<< orphan*/  ZEND_ACC_PUBLIC ; 
 scalar_t__ Z_TYPE_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  add_next_index_zval (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reflection_property_factory (int /*<<< orphan*/ *,int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static void _adddynproperty(zval *ptr, zend_string *key, zend_class_entry *ce, zval *retval)
{
	zend_property_info property_info;
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

	property_info.doc_comment = NULL;
	property_info.flags = ZEND_ACC_PUBLIC;
	property_info.name = key;
	property_info.ce = ce;
	property_info.offset = -1;
	reflection_property_factory(ce, key, &property_info, &property, 1);
	add_next_index_zval(retval, &property);
}