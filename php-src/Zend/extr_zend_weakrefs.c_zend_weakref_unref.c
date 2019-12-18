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
struct TYPE_2__ {int /*<<< orphan*/ * referent; } ;
typedef  TYPE_1__ zend_weakref ;

/* Variables and functions */
 int /*<<< orphan*/  GC_DEL_FLAGS (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IS_OBJ_WEAKLY_REFERENCED ; 
 scalar_t__ Z_PTR_P (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void zend_weakref_unref(zval *zv) {
	zend_weakref *wr = (zend_weakref*) Z_PTR_P(zv);

	GC_DEL_FLAGS(wr->referent, IS_OBJ_WEAKLY_REFERENCED);

	wr->referent = NULL;
}