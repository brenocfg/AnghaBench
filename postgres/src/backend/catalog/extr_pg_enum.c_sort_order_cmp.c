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
struct TYPE_2__ {scalar_t__ enumsortorder; } ;
typedef  int /*<<< orphan*/  HeapTuple ;
typedef  TYPE_1__* Form_pg_enum ;

/* Variables and functions */
 int /*<<< orphan*/  GETSTRUCT (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
sort_order_cmp(const void *p1, const void *p2)
{
	HeapTuple	v1 = *((const HeapTuple *) p1);
	HeapTuple	v2 = *((const HeapTuple *) p2);
	Form_pg_enum en1 = (Form_pg_enum) GETSTRUCT(v1);
	Form_pg_enum en2 = (Form_pg_enum) GETSTRUCT(v2);

	if (en1->enumsortorder < en2->enumsortorder)
		return -1;
	else if (en1->enumsortorder > en2->enumsortorder)
		return 1;
	else
		return 0;
}