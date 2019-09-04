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
typedef  int /*<<< orphan*/  zend_object ;
struct TYPE_3__ {int ar_flags; } ;
typedef  TYPE_1__ spl_array_object ;

/* Variables and functions */
 int SPL_ARRAY_ARRAY_AS_PROPS ; 
 int /*<<< orphan*/  ZEND_PROPERTY_EXISTS ; 
 int /*<<< orphan*/  ZVAL_STR (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_1__* spl_array_from_obj (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spl_array_write_dimension (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zend_std_has_property (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * zend_std_write_property (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ *,void**) ; 

__attribute__((used)) static zval *spl_array_write_property(zend_object *object, zend_string *name, zval *value, void **cache_slot) /* {{{ */
{
	spl_array_object *intern = spl_array_from_obj(object);

	if ((intern->ar_flags & SPL_ARRAY_ARRAY_AS_PROPS) != 0
	&& !zend_std_has_property(object, name, ZEND_PROPERTY_EXISTS, NULL)) {
		zval member;
		ZVAL_STR(&member, name);
		spl_array_write_dimension(object, &member, value);
		return value;
	}
	return zend_std_write_property(object, name, value, cache_slot);
}