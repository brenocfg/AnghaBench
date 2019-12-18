#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct range {scalar_t__ start; } ;

/* Variables and functions */

__attribute__((used)) static int cmp_range(const void *x1, const void *x2)
{
	const struct range *r1 = x1;
	const struct range *r2 = x2;

	if (r1->start < r2->start)
		return -1;
	if (r1->start > r2->start)
		return 1;
	return 0;
}