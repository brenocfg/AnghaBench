#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct extent_buffer {TYPE_2__** pages; } ;
struct btrfs_root {struct btrfs_fs_info* fs_info; } ;
struct btrfs_key {int dummy; } ;
struct btrfs_fs_info {int dummy; } ;
struct TYPE_6__ {struct btrfs_root* root; } ;
struct TYPE_5__ {TYPE_1__* mapping; } ;
struct TYPE_4__ {int /*<<< orphan*/  host; } ;

/* Variables and functions */
 TYPE_3__* BTRFS_I (int /*<<< orphan*/ ) ; 
 int btree_read_extent_buffer_pages (struct btrfs_fs_info*,struct extent_buffer*,int /*<<< orphan*/ ,int,struct btrfs_key*) ; 

int btrfs_read_buffer(struct extent_buffer *buf, u64 parent_transid, int level,
		      struct btrfs_key *first_key)
{
	struct btrfs_root *root = BTRFS_I(buf->pages[0]->mapping->host)->root;
	struct btrfs_fs_info *fs_info = root->fs_info;

	return btree_read_extent_buffer_pages(fs_info, buf, parent_transid,
					      level, first_key);
}