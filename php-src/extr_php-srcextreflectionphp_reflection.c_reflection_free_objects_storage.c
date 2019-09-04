#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zend_object ;
struct TYPE_5__ {int ref_type; int /*<<< orphan*/  obj; int /*<<< orphan*/ * ptr; } ;
typedef  TYPE_1__ reflection_object ;
struct TYPE_6__ {int /*<<< orphan*/  unmangled_name; } ;
typedef  TYPE_2__ property_reference ;
struct TYPE_7__ {int /*<<< orphan*/ * fptr; } ;
typedef  TYPE_3__ parameter_reference ;

/* Variables and functions */
#define  REF_TYPE_CLASS_CONSTANT 134 
#define  REF_TYPE_FUNCTION 133 
#define  REF_TYPE_GENERATOR 132 
#define  REF_TYPE_OTHER 131 
#define  REF_TYPE_PARAMETER 130 
#define  REF_TYPE_PROPERTY 129 
#define  REF_TYPE_TYPE 128 
 int /*<<< orphan*/  _free_function (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  efree (int /*<<< orphan*/ *) ; 
 TYPE_1__* reflection_object_from_obj (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zend_object_std_dtor (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zend_string_release_ex (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  zval_ptr_dtor (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void reflection_free_objects_storage(zend_object *object) /* {{{ */
{
	reflection_object *intern = reflection_object_from_obj(object);
	parameter_reference *reference;
	property_reference *prop_reference;

	if (intern->ptr) {
		switch (intern->ref_type) {
		case REF_TYPE_PARAMETER:
			reference = (parameter_reference*)intern->ptr;
			_free_function(reference->fptr);
			efree(intern->ptr);
			break;
		case REF_TYPE_TYPE:
			efree(intern->ptr);
			break;
		case REF_TYPE_FUNCTION:
			_free_function(intern->ptr);
			break;
		case REF_TYPE_PROPERTY:
			prop_reference = (property_reference*)intern->ptr;
			zend_string_release_ex(prop_reference->unmangled_name, 0);
			efree(intern->ptr);
			break;
		case REF_TYPE_GENERATOR:
		case REF_TYPE_CLASS_CONSTANT:
		case REF_TYPE_OTHER:
			break;
		}
	}
	intern->ptr = NULL;
	zval_ptr_dtor(&intern->obj);
	zend_object_std_dtor(object);
}