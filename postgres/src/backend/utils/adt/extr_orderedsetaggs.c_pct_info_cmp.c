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
struct pct_info {scalar_t__ first_row; scalar_t__ second_row; } ;

/* Variables and functions */

__attribute__((used)) static int
pct_info_cmp(const void *pa, const void *pb)
{
	const struct pct_info *a = (const struct pct_info *) pa;
	const struct pct_info *b = (const struct pct_info *) pb;

	if (a->first_row != b->first_row)
		return (a->first_row < b->first_row) ? -1 : 1;
	if (a->second_row != b->second_row)
		return (a->second_row < b->second_row) ? -1 : 1;
	return 0;
}