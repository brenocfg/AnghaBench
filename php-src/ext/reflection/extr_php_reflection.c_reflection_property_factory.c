#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_13__   TYPE_5__ ;
typedef  struct TYPE_12__   TYPE_4__ ;
typedef  struct TYPE_11__   TYPE_3__ ;
typedef  struct TYPE_10__   TYPE_2__ ;
typedef  struct TYPE_9__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zval ;
typedef  int /*<<< orphan*/  zend_string ;
struct TYPE_10__ {TYPE_1__* ce; } ;
typedef  TYPE_2__ zend_property_info ;
struct TYPE_11__ {int /*<<< orphan*/ * name; } ;
typedef  TYPE_3__ zend_class_entry ;
struct TYPE_12__ {scalar_t__ ignore_visibility; TYPE_3__* ce; int /*<<< orphan*/  ref_type; TYPE_5__* ptr; } ;
typedef  TYPE_4__ reflection_object ;
struct TYPE_13__ {int /*<<< orphan*/  unmangled_name; TYPE_2__* prop; } ;
typedef  TYPE_5__ property_reference ;
struct TYPE_9__ {int /*<<< orphan*/ * name; } ;

/* Variables and functions */
 int /*<<< orphan*/  REF_TYPE_PROPERTY ; 
 int /*<<< orphan*/  ZVAL_STR_COPY (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 TYPE_4__* Z_REFLECTION_P (int /*<<< orphan*/ *) ; 
 scalar_t__ emalloc (int) ; 
 int /*<<< orphan*/  reflection_instantiate (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reflection_prop_class (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reflection_prop_name (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reflection_property_ptr ; 
 int /*<<< orphan*/  zend_string_copy (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void reflection_property_factory(zend_class_entry *ce, zend_string *name, zend_property_info *prop, zval *object)
{
	reflection_object *intern;
	property_reference *reference;

	reflection_instantiate(reflection_property_ptr, object);
	intern = Z_REFLECTION_P(object);
	reference = (property_reference*) emalloc(sizeof(property_reference));
	reference->prop = prop;
	reference->unmangled_name = zend_string_copy(name);
	intern->ptr = reference;
	intern->ref_type = REF_TYPE_PROPERTY;
	intern->ce = ce;
	intern->ignore_visibility = 0;
	ZVAL_STR_COPY(reflection_prop_name(object), name);
	ZVAL_STR_COPY(reflection_prop_class(object), prop ? prop->ce->name : ce->name);
}