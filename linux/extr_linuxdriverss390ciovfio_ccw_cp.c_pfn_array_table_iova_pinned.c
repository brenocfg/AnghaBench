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
struct pfn_array_table {int pat_nr; struct pfn_array* pat_pa; } ;
struct pfn_array {int pa_nr; unsigned long* pa_iova_pfn; } ;

/* Variables and functions */
 unsigned long PAGE_SHIFT ; 

__attribute__((used)) static bool pfn_array_table_iova_pinned(struct pfn_array_table *pat,
					unsigned long iova)
{
	struct pfn_array *pa = pat->pat_pa;
	unsigned long iova_pfn = iova >> PAGE_SHIFT;
	int i, j;

	for (i = 0; i < pat->pat_nr; i++, pa++)
		for (j = 0; j < pa->pa_nr; j++)
			if (pa->pa_iova_pfn[j] == iova_pfn)
				return true;

	return false;
}