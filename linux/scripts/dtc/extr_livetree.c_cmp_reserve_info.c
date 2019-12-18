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
struct reserve_info {scalar_t__ address; scalar_t__ size; } ;

/* Variables and functions */

__attribute__((used)) static int cmp_reserve_info(const void *ax, const void *bx)
{
	const struct reserve_info *a, *b;

	a = *((const struct reserve_info * const *)ax);
	b = *((const struct reserve_info * const *)bx);

	if (a->address < b->address)
		return -1;
	else if (a->address > b->address)
		return 1;
	else if (a->size < b->size)
		return -1;
	else if (a->size > b->size)
		return 1;
	else
		return 0;
}