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
typedef  scalar_t__ zend_long ;
struct TYPE_3__ {scalar_t__ size; int /*<<< orphan*/ * elements; } ;
typedef  TYPE_1__ spl_fixedarray ;

/* Variables and functions */
 int /*<<< orphan*/ * ecalloc (scalar_t__,int) ; 

__attribute__((used)) static void spl_fixedarray_init(spl_fixedarray *array, zend_long size) /* {{{ */
{
	if (size > 0) {
		array->size = 0; /* reset size in case ecalloc() fails */
		array->elements = ecalloc(size, sizeof(zval));
		array->size = size;
	} else {
		array->elements = NULL;
		array->size = 0;
	}
}