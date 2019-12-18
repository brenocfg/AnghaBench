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
typedef  int /*<<< orphan*/  zval ;
struct TYPE_5__ {scalar_t__ ptr; } ;
typedef  TYPE_1__ mysqli_object ;
struct TYPE_7__ {scalar_t__ ptr; } ;
struct TYPE_6__ {int /*<<< orphan*/  reason; } ;
typedef  TYPE_2__ MYSQLI_WARNING ;
typedef  TYPE_3__ MYSQLI_RESOURCE ;

/* Variables and functions */
 int /*<<< orphan*/  ZVAL_COPY (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static
zval *mysqli_warning_message(mysqli_object *obj, zval *retval)
{
	MYSQLI_WARNING *w;

	if (!obj->ptr || !((MYSQLI_RESOURCE *)(obj->ptr))->ptr) {
		return NULL;
	}

	w = (MYSQLI_WARNING *)((MYSQLI_RESOURCE *)(obj->ptr))->ptr;
	ZVAL_COPY(retval, &w->reason);
	return retval;
}