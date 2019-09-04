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
struct range {scalar_t__ end; scalar_t__ start; } ;

/* Variables and functions */
 int /*<<< orphan*/  cmp_range ; 
 int /*<<< orphan*/  sort (struct range*,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

int clean_sort_range(struct range *range, int az)
{
	int i, j, k = az - 1, nr_range = az;

	for (i = 0; i < k; i++) {
		if (range[i].end)
			continue;
		for (j = k; j > i; j--) {
			if (range[j].end) {
				k = j;
				break;
			}
		}
		if (j == i)
			break;
		range[i].start = range[k].start;
		range[i].end   = range[k].end;
		range[k].start = 0;
		range[k].end   = 0;
		k--;
	}
	/* count it */
	for (i = 0; i < az; i++) {
		if (!range[i].end) {
			nr_range = i;
			break;
		}
	}

	/* sort them */
	sort(range, nr_range, sizeof(struct range), cmp_range, NULL);

	return nr_range;
}