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
struct pcpu_chunk {int dummy; } ;
struct page {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  pcpu_free_pages (struct pcpu_chunk*,struct page**,int,int) ; 
 struct page** pcpu_get_pages () ; 
 int /*<<< orphan*/  pcpu_pre_unmap_flush (struct pcpu_chunk*,int,int) ; 
 int /*<<< orphan*/  pcpu_unmap_pages (struct pcpu_chunk*,struct page**,int,int) ; 

__attribute__((used)) static void pcpu_depopulate_chunk(struct pcpu_chunk *chunk,
				  int page_start, int page_end)
{
	struct page **pages;

	/*
	 * If control reaches here, there must have been at least one
	 * successful population attempt so the temp pages array must
	 * be available now.
	 */
	pages = pcpu_get_pages();
	BUG_ON(!pages);

	/* unmap and free */
	pcpu_pre_unmap_flush(chunk, page_start, page_end);

	pcpu_unmap_pages(chunk, pages, page_start, page_end);

	/* no need to flush tlb, vmalloc will handle it lazily */

	pcpu_free_pages(chunk, pages, page_start, page_end);
}