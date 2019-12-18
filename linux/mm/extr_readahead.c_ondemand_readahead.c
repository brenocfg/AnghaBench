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
struct file_ra_state {unsigned long ra_pages; unsigned long start; unsigned long size; unsigned long async_size; scalar_t__ prev_pos; } ;
struct file {int dummy; } ;
struct backing_dev_info {unsigned long io_pages; } ;
struct address_space {int /*<<< orphan*/  host; } ;
typedef  unsigned long pgoff_t ;

/* Variables and functions */
 unsigned long long PAGE_SHIFT ; 
 unsigned long __do_page_cache_readahead (struct address_space*,struct file*,unsigned long,unsigned long,int /*<<< orphan*/ ) ; 
 unsigned long get_init_ra_size (unsigned long,unsigned long) ; 
 void* get_next_ra_size (struct file_ra_state*,unsigned long) ; 
 struct backing_dev_info* inode_to_bdi (int /*<<< orphan*/ ) ; 
 unsigned long min (unsigned long,unsigned long) ; 
 unsigned long page_cache_next_miss (struct address_space*,unsigned long,unsigned long) ; 
 unsigned long ra_submit (struct file_ra_state*,struct address_space*,struct file*) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 scalar_t__ try_context_readahead (struct address_space*,struct file_ra_state*,unsigned long,unsigned long,unsigned long) ; 

__attribute__((used)) static unsigned long
ondemand_readahead(struct address_space *mapping,
		   struct file_ra_state *ra, struct file *filp,
		   bool hit_readahead_marker, pgoff_t offset,
		   unsigned long req_size)
{
	struct backing_dev_info *bdi = inode_to_bdi(mapping->host);
	unsigned long max_pages = ra->ra_pages;
	unsigned long add_pages;
	pgoff_t prev_offset;

	/*
	 * If the request exceeds the readahead window, allow the read to
	 * be up to the optimal hardware IO size
	 */
	if (req_size > max_pages && bdi->io_pages > max_pages)
		max_pages = min(req_size, bdi->io_pages);

	/*
	 * start of file
	 */
	if (!offset)
		goto initial_readahead;

	/*
	 * It's the expected callback offset, assume sequential access.
	 * Ramp up sizes, and push forward the readahead window.
	 */
	if ((offset == (ra->start + ra->size - ra->async_size) ||
	     offset == (ra->start + ra->size))) {
		ra->start += ra->size;
		ra->size = get_next_ra_size(ra, max_pages);
		ra->async_size = ra->size;
		goto readit;
	}

	/*
	 * Hit a marked page without valid readahead state.
	 * E.g. interleaved reads.
	 * Query the pagecache for async_size, which normally equals to
	 * readahead size. Ramp it up and use it as the new readahead size.
	 */
	if (hit_readahead_marker) {
		pgoff_t start;

		rcu_read_lock();
		start = page_cache_next_miss(mapping, offset + 1, max_pages);
		rcu_read_unlock();

		if (!start || start - offset > max_pages)
			return 0;

		ra->start = start;
		ra->size = start - offset;	/* old async_size */
		ra->size += req_size;
		ra->size = get_next_ra_size(ra, max_pages);
		ra->async_size = ra->size;
		goto readit;
	}

	/*
	 * oversize read
	 */
	if (req_size > max_pages)
		goto initial_readahead;

	/*
	 * sequential cache miss
	 * trivial case: (offset - prev_offset) == 1
	 * unaligned reads: (offset - prev_offset) == 0
	 */
	prev_offset = (unsigned long long)ra->prev_pos >> PAGE_SHIFT;
	if (offset - prev_offset <= 1UL)
		goto initial_readahead;

	/*
	 * Query the page cache and look for the traces(cached history pages)
	 * that a sequential stream would leave behind.
	 */
	if (try_context_readahead(mapping, ra, offset, req_size, max_pages))
		goto readit;

	/*
	 * standalone, small random read
	 * Read as is, and do not pollute the readahead state.
	 */
	return __do_page_cache_readahead(mapping, filp, offset, req_size, 0);

initial_readahead:
	ra->start = offset;
	ra->size = get_init_ra_size(req_size, max_pages);
	ra->async_size = ra->size > req_size ? ra->size - req_size : ra->size;

readit:
	/*
	 * Will this read hit the readahead marker made by itself?
	 * If so, trigger the readahead marker hit now, and merge
	 * the resulted next readahead window into the current one.
	 * Take care of maximum IO pages as above.
	 */
	if (offset == ra->start && ra->size == ra->async_size) {
		add_pages = get_next_ra_size(ra, max_pages);
		if (ra->size + add_pages <= max_pages) {
			ra->async_size = add_pages;
			ra->size += add_pages;
		} else {
			ra->size = max_pages;
			ra->async_size = max_pages >> 1;
		}
	}

	return ra_submit(ra, mapping, filp);
}