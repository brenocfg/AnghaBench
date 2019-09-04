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
typedef  scalar_t__ uint32_t ;
struct interval {scalar_t__ last; scalar_t__ first; } ;

/* Variables and functions */

__attribute__((used)) static int ucs_cmp(const void *key, const void *elt)
{
	uint32_t ucs = *(uint32_t *)key;
	struct interval e = *(struct interval *) elt;

	if (ucs > e.last)
		return 1;
	else if (ucs < e.first)
		return -1;
	return 0;
}