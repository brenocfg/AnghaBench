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
struct inode {int /*<<< orphan*/  i_mapping; } ;
struct file_ra_state {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_NOFS ; 
 int PAGE_SHIFT ; 
 int /*<<< orphan*/  file_ra_state_init (struct file_ra_state*,int /*<<< orphan*/ ) ; 
 int i_size_read (struct inode*) ; 
 int /*<<< orphan*/  kfree (struct file_ra_state*) ; 
 struct file_ra_state* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  page_cache_sync_readahead (int /*<<< orphan*/ ,struct file_ra_state*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static void readahead_cache(struct inode *inode)
{
	struct file_ra_state *ra;
	unsigned long last_index;

	ra = kzalloc(sizeof(*ra), GFP_NOFS);
	if (!ra)
		return;

	file_ra_state_init(ra, inode->i_mapping);
	last_index = (i_size_read(inode) - 1) >> PAGE_SHIFT;

	page_cache_sync_readahead(inode->i_mapping, ra, NULL, 0, last_index);

	kfree(ra);
}