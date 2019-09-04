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
typedef  int /*<<< orphan*/  zend_object ;
struct TYPE_3__ {int /*<<< orphan*/  array; } ;
typedef  TYPE_1__ spl_array_object ;
typedef  int /*<<< orphan*/  HashTable ;

/* Variables and functions */
 TYPE_1__* spl_array_from_obj (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * zend_std_get_properties (int /*<<< orphan*/ *) ; 

__attribute__((used)) static HashTable *spl_array_get_gc(zend_object *obj, zval **gc_data, int *gc_data_count) /* {{{ */
{
	spl_array_object *intern = spl_array_from_obj(obj);
	*gc_data = &intern->array;
	*gc_data_count = 1;
	return zend_std_get_properties(obj);
}