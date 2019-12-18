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
struct uid_gid_extent {scalar_t__ lower_first; } ;

/* Variables and functions */

__attribute__((used)) static int cmp_extents_reverse(const void *a, const void *b)
{
	const struct uid_gid_extent *e1 = a;
	const struct uid_gid_extent *e2 = b;

	if (e1->lower_first < e2->lower_first)
		return -1;

	if (e1->lower_first > e2->lower_first)
		return 1;

	return 0;
}