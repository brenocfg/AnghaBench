#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  zval ;
typedef  int /*<<< orphan*/  spl_array_object ;
struct TYPE_2__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  ZSTR_VAL (int /*<<< orphan*/ ) ; 
 TYPE_1__* Z_OBJCE_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  Z_OBJ_P (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/ * Z_SPLARRAY_P (int /*<<< orphan*/ *) ; 
 scalar_t__ spl_array_is_object (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spl_array_write_dimension (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  zend_throw_error (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 

void spl_array_iterator_append(zval *object, zval *append_value) /* {{{ */
{
	spl_array_object *intern = Z_SPLARRAY_P(object);

	if (spl_array_is_object(intern)) {
		zend_throw_error(NULL, "Cannot append properties to objects, use %s::offsetSet() instead", ZSTR_VAL(Z_OBJCE_P(object)->name));
		return;
	}

	spl_array_write_dimension(Z_OBJ_P(object), NULL, append_value);
}