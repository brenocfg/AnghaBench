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
typedef  int /*<<< orphan*/  zend_object ;
struct TYPE_4__ {int ar_flags; scalar_t__ fptr_offset_get; } ;
typedef  TYPE_1__ spl_array_object ;

/* Variables and functions */
 int SPL_ARRAY_ARRAY_AS_PROPS ; 
 int /*<<< orphan*/  ZEND_PROPERTY_EXISTS ; 
 int /*<<< orphan*/  ZVAL_STR (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_1__* spl_array_from_obj (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * spl_array_get_dimension_ptr (int,TYPE_1__*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/ * zend_std_get_property_ptr_ptr (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,void**) ; 
 int /*<<< orphan*/  zend_std_has_property (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static zval *spl_array_get_property_ptr_ptr(zend_object *object, zend_string *name, int type, void **cache_slot) /* {{{ */
{
	spl_array_object *intern = spl_array_from_obj(object);

	if ((intern->ar_flags & SPL_ARRAY_ARRAY_AS_PROPS) != 0
		&& !zend_std_has_property(object, name, ZEND_PROPERTY_EXISTS, NULL)) {
		/* If object has offsetGet() overridden, then fallback to read_property,
		 * which will call offsetGet(). */
		zval member;
		if (intern->fptr_offset_get) {
			return NULL;
		}
		ZVAL_STR(&member, name);
		return spl_array_get_dimension_ptr(1, intern, &member, type);
	}
	return zend_std_get_property_ptr_ptr(object, name, type, cache_slot);
}