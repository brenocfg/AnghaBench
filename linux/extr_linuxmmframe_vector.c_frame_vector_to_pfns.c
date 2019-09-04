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
struct page {int dummy; } ;
struct frame_vector {int is_pfns; int nr_frames; scalar_t__ ptrs; } ;

/* Variables and functions */
 unsigned long page_to_pfn (struct page*) ; 

void frame_vector_to_pfns(struct frame_vector *vec)
{
	int i;
	unsigned long *nums;
	struct page **pages;

	if (vec->is_pfns)
		return;
	pages = (struct page **)(vec->ptrs);
	nums = (unsigned long *)pages;
	for (i = 0; i < vec->nr_frames; i++)
		nums[i] = page_to_pfn(pages[i]);
	vec->is_pfns = true;
}