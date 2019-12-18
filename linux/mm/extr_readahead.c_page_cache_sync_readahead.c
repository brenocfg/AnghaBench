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
struct file_ra_state {int /*<<< orphan*/  ra_pages; } ;
struct file {int f_mode; } ;
struct address_space {int dummy; } ;
typedef  int /*<<< orphan*/  pgoff_t ;

/* Variables and functions */
 int FMODE_RANDOM ; 
 scalar_t__ blk_cgroup_congested () ; 
 int /*<<< orphan*/  force_page_cache_readahead (struct address_space*,struct file*,int /*<<< orphan*/ ,unsigned long) ; 
 int /*<<< orphan*/  ondemand_readahead (struct address_space*,struct file_ra_state*,struct file*,int,int /*<<< orphan*/ ,unsigned long) ; 

void page_cache_sync_readahead(struct address_space *mapping,
			       struct file_ra_state *ra, struct file *filp,
			       pgoff_t offset, unsigned long req_size)
{
	/* no read-ahead */
	if (!ra->ra_pages)
		return;

	if (blk_cgroup_congested())
		return;

	/* be dumb */
	if (filp && (filp->f_mode & FMODE_RANDOM)) {
		force_page_cache_readahead(mapping, filp, offset, req_size);
		return;
	}

	/* do read-ahead */
	ondemand_readahead(mapping, ra, filp, false, offset, req_size);
}