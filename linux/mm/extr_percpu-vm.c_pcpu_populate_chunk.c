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
typedef  int /*<<< orphan*/  gfp_t ;

/* Variables and functions */
 int ENOMEM ; 
 scalar_t__ pcpu_alloc_pages (struct pcpu_chunk*,struct page**,int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pcpu_free_pages (struct pcpu_chunk*,struct page**,int,int) ; 
 struct page** pcpu_get_pages () ; 
 scalar_t__ pcpu_map_pages (struct pcpu_chunk*,struct page**,int,int) ; 
 int /*<<< orphan*/  pcpu_post_map_flush (struct pcpu_chunk*,int,int) ; 

__attribute__((used)) static int pcpu_populate_chunk(struct pcpu_chunk *chunk,
			       int page_start, int page_end, gfp_t gfp)
{
	struct page **pages;

	pages = pcpu_get_pages();
	if (!pages)
		return -ENOMEM;

	if (pcpu_alloc_pages(chunk, pages, page_start, page_end, gfp))
		return -ENOMEM;

	if (pcpu_map_pages(chunk, pages, page_start, page_end)) {
		pcpu_free_pages(chunk, pages, page_start, page_end);
		return -ENOMEM;
	}
	pcpu_post_map_flush(chunk, page_start, page_end);

	return 0;
}