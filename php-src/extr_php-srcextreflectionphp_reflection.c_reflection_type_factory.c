#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zval ;
typedef  int /*<<< orphan*/  zend_type ;
struct TYPE_4__ {int /*<<< orphan*/  type; } ;
typedef  TYPE_1__ type_reference ;
struct TYPE_5__ {int /*<<< orphan*/  ref_type; TYPE_1__* ptr; } ;
typedef  TYPE_2__ reflection_object ;

/* Variables and functions */
 int /*<<< orphan*/  REF_TYPE_TYPE ; 
 TYPE_2__* Z_REFLECTION_P (int /*<<< orphan*/ *) ; 
 scalar_t__ emalloc (int) ; 
 int /*<<< orphan*/  reflection_instantiate (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  reflection_named_type_ptr ; 

__attribute__((used)) static void reflection_type_factory(zend_type type, zval *object)
{
	reflection_object *intern;
	type_reference *reference;

	reflection_instantiate(reflection_named_type_ptr, object);
	intern = Z_REFLECTION_P(object);
	reference = (type_reference*) emalloc(sizeof(type_reference));
	reference->type = type;
	intern->ptr = reference;
	intern->ref_type = REF_TYPE_TYPE;
}