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
struct TYPE_3__ {int ce_flags; int /*<<< orphan*/  refcount; } ;
typedef  TYPE_1__ zend_class_entry ;

/* Variables and functions */
 int ZEND_ACC_IMMUTABLE ; 
 TYPE_1__* Z_PTR_P (int /*<<< orphan*/ *) ; 

void zend_class_add_ref(zval *zv)
{
	zend_class_entry *ce = Z_PTR_P(zv);

	if (!(ce->ce_flags & ZEND_ACC_IMMUTABLE)) {
		ce->refcount++;
	}
}