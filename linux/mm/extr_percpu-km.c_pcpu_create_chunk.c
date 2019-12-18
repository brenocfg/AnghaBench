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
struct pcpu_chunk {int /*<<< orphan*/  base_addr; struct page* data; } ;
struct page {int dummy; } ;
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int PAGE_SHIFT ; 
 struct page* alloc_pages (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nth_page (struct page*,int) ; 
 int /*<<< orphan*/  order_base_2 (int const) ; 
 int /*<<< orphan*/  page_address (struct page*) ; 
 struct pcpu_chunk* pcpu_alloc_chunk (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pcpu_chunk_populated (struct pcpu_chunk*,int /*<<< orphan*/ ,int const) ; 
 int /*<<< orphan*/  pcpu_free_chunk (struct pcpu_chunk*) ; 
 int* pcpu_group_sizes ; 
 int /*<<< orphan*/  pcpu_lock ; 
 int /*<<< orphan*/  pcpu_set_page_chunk (int /*<<< orphan*/ ,struct pcpu_chunk*) ; 
 int /*<<< orphan*/  pcpu_stats_chunk_alloc () ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  trace_percpu_create_chunk (int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct pcpu_chunk *pcpu_create_chunk(gfp_t gfp)
{
	const int nr_pages = pcpu_group_sizes[0] >> PAGE_SHIFT;
	struct pcpu_chunk *chunk;
	struct page *pages;
	unsigned long flags;
	int i;

	chunk = pcpu_alloc_chunk(gfp);
	if (!chunk)
		return NULL;

	pages = alloc_pages(gfp, order_base_2(nr_pages));
	if (!pages) {
		pcpu_free_chunk(chunk);
		return NULL;
	}

	for (i = 0; i < nr_pages; i++)
		pcpu_set_page_chunk(nth_page(pages, i), chunk);

	chunk->data = pages;
	chunk->base_addr = page_address(pages);

	spin_lock_irqsave(&pcpu_lock, flags);
	pcpu_chunk_populated(chunk, 0, nr_pages);
	spin_unlock_irqrestore(&pcpu_lock, flags);

	pcpu_stats_chunk_alloc();
	trace_percpu_create_chunk(chunk->base_addr);

	return chunk;
}