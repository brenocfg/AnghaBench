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
struct ring_buffer {long aux_nr_pages; unsigned long aux_pgoff; int /*<<< orphan*/ * aux_pages; } ;
struct page {int dummy; } ;

/* Variables and functions */
 struct page* __perf_mmap_to_page (struct ring_buffer*,unsigned long) ; 
 int array_index_nospec (unsigned long,unsigned long) ; 
 struct page* virt_to_page (int /*<<< orphan*/ ) ; 

struct page *
perf_mmap_to_page(struct ring_buffer *rb, unsigned long pgoff)
{
	if (rb->aux_nr_pages) {
		/* above AUX space */
		if (pgoff > rb->aux_pgoff + rb->aux_nr_pages)
			return NULL;

		/* AUX space */
		if (pgoff >= rb->aux_pgoff) {
			int aux_pgoff = array_index_nospec(pgoff - rb->aux_pgoff, rb->aux_nr_pages);
			return virt_to_page(rb->aux_pages[aux_pgoff]);
		}
	}

	return __perf_mmap_to_page(rb, pgoff);
}