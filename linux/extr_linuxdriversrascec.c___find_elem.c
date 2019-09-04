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
typedef  scalar_t__ u64 ;
struct ce_array {int n; int /*<<< orphan*/ * array; } ;

/* Variables and functions */
 int ENOKEY ; 
 scalar_t__ PFN (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int __find_elem(struct ce_array *ca, u64 pfn, unsigned int *to)
{
	u64 this_pfn;
	int min = 0, max = ca->n;

	while (min < max) {
		int tmp = (max + min) >> 1;

		this_pfn = PFN(ca->array[tmp]);

		if (this_pfn < pfn)
			min = tmp + 1;
		else if (this_pfn > pfn)
			max = tmp;
		else {
			min = tmp;
			break;
		}
	}

	if (to)
		*to = min;

	this_pfn = PFN(ca->array[min]);

	if (this_pfn == pfn)
		return min;

	return -ENOKEY;
}