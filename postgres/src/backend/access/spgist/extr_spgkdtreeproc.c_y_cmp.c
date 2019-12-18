#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {TYPE_1__* p; } ;
struct TYPE_3__ {scalar_t__ y; } ;
typedef  TYPE_2__ SortedPoint ;

/* Variables and functions */

__attribute__((used)) static int
y_cmp(const void *a, const void *b)
{
	SortedPoint *pa = (SortedPoint *) a;
	SortedPoint *pb = (SortedPoint *) b;

	if (pa->p->y == pb->p->y)
		return 0;
	return (pa->p->y > pb->p->y) ? 1 : -1;
}