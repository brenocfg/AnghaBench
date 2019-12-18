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
struct TYPE_2__ {scalar_t__ name; } ;
typedef  TYPE_1__ pivot_field ;

/* Variables and functions */
 int strcmp (scalar_t__,scalar_t__) ; 

__attribute__((used)) static int
pivotFieldCompare(const void *a, const void *b)
{
	const pivot_field *pa = (const pivot_field *) a;
	const pivot_field *pb = (const pivot_field *) b;

	/* test null values */
	if (!pb->name)
		return pa->name ? -1 : 0;
	else if (!pa->name)
		return 1;

	/* non-null values */
	return strcmp(pa->name, pb->name);
}