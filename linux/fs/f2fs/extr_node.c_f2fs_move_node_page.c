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
struct writeback_control {int nr_to_write; int /*<<< orphan*/  for_reclaim; int /*<<< orphan*/  sync_mode; } ;
struct page {int dummy; } ;

/* Variables and functions */
 int EAGAIN ; 
 int FG_GC ; 
 int /*<<< orphan*/  FS_GC_NODE_IO ; 
 int /*<<< orphan*/  NODE ; 
 int /*<<< orphan*/  PageWriteback (struct page*) ; 
 int /*<<< orphan*/  WB_SYNC_ALL ; 
 scalar_t__ __write_node_page (struct page*,int,int /*<<< orphan*/ *,struct writeback_control*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  clear_page_dirty_for_io (struct page*) ; 
 int /*<<< orphan*/  f2fs_put_page (struct page*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  f2fs_wait_on_page_writeback (struct page*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  set_page_dirty (struct page*) ; 
 int /*<<< orphan*/  unlock_page (struct page*) ; 

int f2fs_move_node_page(struct page *node_page, int gc_type)
{
	int err = 0;

	if (gc_type == FG_GC) {
		struct writeback_control wbc = {
			.sync_mode = WB_SYNC_ALL,
			.nr_to_write = 1,
			.for_reclaim = 0,
		};

		f2fs_wait_on_page_writeback(node_page, NODE, true, true);

		set_page_dirty(node_page);

		if (!clear_page_dirty_for_io(node_page)) {
			err = -EAGAIN;
			goto out_page;
		}

		if (__write_node_page(node_page, false, NULL,
					&wbc, false, FS_GC_NODE_IO, NULL)) {
			err = -EAGAIN;
			unlock_page(node_page);
		}
		goto release_page;
	} else {
		/* set page dirty and write it */
		if (!PageWriteback(node_page))
			set_page_dirty(node_page);
	}
out_page:
	unlock_page(node_page);
release_page:
	f2fs_put_page(node_page, 0);
	return err;
}