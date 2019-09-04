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
struct file_ra_state {int /*<<< orphan*/  ra_pages; } ;
struct file {int dummy; } ;
struct address_space {int /*<<< orphan*/  host; } ;
typedef  int /*<<< orphan*/  pgoff_t ;

/* Variables and functions */
 int /*<<< orphan*/  ClearPageReadahead (struct page*) ; 
 scalar_t__ PageWriteback (struct page*) ; 
 scalar_t__ blk_cgroup_congested () ; 
 scalar_t__ inode_read_congested (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ondemand_readahead (struct address_space*,struct file_ra_state*,struct file*,int,int /*<<< orphan*/ ,unsigned long) ; 

void
page_cache_async_readahead(struct address_space *mapping,
			   struct file_ra_state *ra, struct file *filp,
			   struct page *page, pgoff_t offset,
			   unsigned long req_size)
{
	/* no read-ahead */
	if (!ra->ra_pages)
		return;

	/*
	 * Same bit is used for PG_readahead and PG_reclaim.
	 */
	if (PageWriteback(page))
		return;

	ClearPageReadahead(page);

	/*
	 * Defer asynchronous read-ahead on IO congestion.
	 */
	if (inode_read_congested(mapping->host))
		return;

	if (blk_cgroup_congested())
		return;

	/* do read-ahead */
	ondemand_readahead(mapping, ra, filp, true, offset, req_size);
}