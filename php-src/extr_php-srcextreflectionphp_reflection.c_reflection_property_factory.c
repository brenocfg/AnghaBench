#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zval ;
typedef  int /*<<< orphan*/  zend_string ;
struct TYPE_9__ {int flags; TYPE_2__* ce; } ;
typedef  TYPE_1__ zend_property_info ;
struct TYPE_10__ {int /*<<< orphan*/ * name; struct TYPE_10__* parent; int /*<<< orphan*/  properties_info; } ;
typedef  TYPE_2__ zend_class_entry ;
typedef  int /*<<< orphan*/  zend_bool ;
struct TYPE_11__ {scalar_t__ ignore_visibility; TYPE_2__* ce; int /*<<< orphan*/  ref_type; TYPE_4__* ptr; } ;
typedef  TYPE_3__ reflection_object ;
struct TYPE_12__ {int /*<<< orphan*/  dynamic; int /*<<< orphan*/  unmangled_name; TYPE_1__ prop; } ;
typedef  TYPE_4__ property_reference ;

/* Variables and functions */
 int /*<<< orphan*/  REF_TYPE_PROPERTY ; 
 int ZEND_ACC_PRIVATE ; 
 int /*<<< orphan*/  ZVAL_STR_COPY (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_3__* Z_REFLECTION_P (int /*<<< orphan*/ *) ; 
 scalar_t__ emalloc (int) ; 
 int /*<<< orphan*/  reflection_instantiate (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reflection_property_ptr ; 
 int /*<<< orphan*/  reflection_update_property_class (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reflection_update_property_name (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 TYPE_1__* zend_hash_find_ptr (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zend_string_copy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void reflection_property_factory(zend_class_entry *ce, zend_string *name, zend_property_info *prop, zval *object, zend_bool dynamic)
{
	reflection_object *intern;
	zval propname;
	zval classname;
	property_reference *reference;

	if (!(prop->flags & ZEND_ACC_PRIVATE)) {
		/* we have to search the class hierarchy for this (implicit) public or protected property */
		zend_class_entry *tmp_ce = ce, *store_ce = ce;
		zend_property_info *tmp_info = NULL;

		while (tmp_ce && (tmp_info = zend_hash_find_ptr(&tmp_ce->properties_info, name)) == NULL) {
			ce = tmp_ce;
			tmp_ce = tmp_ce->parent;
		}

		if (tmp_info && (!(tmp_info->flags & ZEND_ACC_PRIVATE) || tmp_info->ce == tmp_ce)) { /* found something and it's not a parent's private */
			prop = tmp_info;
		} else { /* not found, use initial value */
			ce = store_ce;
		}
	}

	ZVAL_STR_COPY(&propname, name);
	ZVAL_STR_COPY(&classname, prop->ce->name);

	reflection_instantiate(reflection_property_ptr, object);
	intern = Z_REFLECTION_P(object);
	reference = (property_reference*) emalloc(sizeof(property_reference));
	reference->prop = *prop;
	reference->unmangled_name = zend_string_copy(name);
	reference->dynamic = dynamic;
	intern->ptr = reference;
	intern->ref_type = REF_TYPE_PROPERTY;
	intern->ce = ce;
	intern->ignore_visibility = 0;
	reflection_update_property_name(object, &propname);
	reflection_update_property_class(object, &classname);
}