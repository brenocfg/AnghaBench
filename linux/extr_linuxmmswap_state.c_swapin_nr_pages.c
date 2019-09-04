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
typedef  int /*<<< orphan*/  atomic_t ;

/* Variables and functions */
 int READ_ONCE (int /*<<< orphan*/ ) ; 
 unsigned int __swapin_nr_pages (unsigned long,unsigned long,unsigned int,unsigned int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,unsigned int) ; 
 unsigned int atomic_xchg (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  page_cluster ; 
 int /*<<< orphan*/  swapin_readahead_hits ; 

__attribute__((used)) static unsigned long swapin_nr_pages(unsigned long offset)
{
	static unsigned long prev_offset;
	unsigned int hits, pages, max_pages;
	static atomic_t last_readahead_pages;

	max_pages = 1 << READ_ONCE(page_cluster);
	if (max_pages <= 1)
		return 1;

	hits = atomic_xchg(&swapin_readahead_hits, 0);
	pages = __swapin_nr_pages(prev_offset, offset, hits, max_pages,
				  atomic_read(&last_readahead_pages));
	if (!hits)
		prev_offset = offset;
	atomic_set(&last_readahead_pages, pages);

	return pages;
}