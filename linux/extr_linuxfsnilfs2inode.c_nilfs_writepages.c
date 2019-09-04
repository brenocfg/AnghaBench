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
struct writeback_control {scalar_t__ sync_mode; int /*<<< orphan*/  range_end; int /*<<< orphan*/  range_start; } ;
struct inode {int /*<<< orphan*/  i_sb; } ;
struct address_space {struct inode* host; } ;

/* Variables and functions */
 int EROFS ; 
 scalar_t__ WB_SYNC_ALL ; 
 int /*<<< orphan*/  nilfs_clear_dirty_pages (struct address_space*,int) ; 
 int nilfs_construct_dsync_segment (int /*<<< orphan*/ ,struct inode*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ sb_rdonly (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nilfs_writepages(struct address_space *mapping,
			    struct writeback_control *wbc)
{
	struct inode *inode = mapping->host;
	int err = 0;

	if (sb_rdonly(inode->i_sb)) {
		nilfs_clear_dirty_pages(mapping, false);
		return -EROFS;
	}

	if (wbc->sync_mode == WB_SYNC_ALL)
		err = nilfs_construct_dsync_segment(inode->i_sb, inode,
						    wbc->range_start,
						    wbc->range_end);
	return err;
}