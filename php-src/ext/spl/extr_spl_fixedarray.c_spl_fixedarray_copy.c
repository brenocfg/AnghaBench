#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int size; int /*<<< orphan*/ * elements; } ;
typedef  TYPE_1__ spl_fixedarray ;

/* Variables and functions */
 int /*<<< orphan*/  ZVAL_COPY (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void spl_fixedarray_copy(spl_fixedarray *to, spl_fixedarray *from) /* {{{ */
{
	int i;
	for (i = 0; i < from->size; i++) {
		ZVAL_COPY(&to->elements[i], &from->elements[i]);
	}
}