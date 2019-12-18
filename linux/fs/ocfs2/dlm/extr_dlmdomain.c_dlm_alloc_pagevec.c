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

/* Variables and functions */
 scalar_t__ DLM_BUCKETS_PER_PAGE ; 
 scalar_t__ DLM_HASH_PAGES ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ __get_free_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dlm_free_pagevec (void**,int) ; 
 void** kmalloc_array (int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*,int,unsigned long,unsigned long) ; 

__attribute__((used)) static void **dlm_alloc_pagevec(int pages)
{
	void **vec = kmalloc_array(pages, sizeof(void *), GFP_KERNEL);
	int i;

	if (!vec)
		return NULL;

	for (i = 0; i < pages; i++)
		if (!(vec[i] = (void *)__get_free_page(GFP_KERNEL)))
			goto out_free;

	mlog(0, "Allocated DLM hash pagevec; %d pages (%lu expected), %lu buckets per page\n",
	     pages, (unsigned long)DLM_HASH_PAGES,
	     (unsigned long)DLM_BUCKETS_PER_PAGE);
	return vec;
out_free:
	dlm_free_pagevec(vec, i);
	return NULL;
}