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
struct fsync_inode_entry {int /*<<< orphan*/  list; int /*<<< orphan*/  inode; } ;

/* Variables and functions */
 int /*<<< orphan*/  f2fs_inode_synced (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fsync_entry_slab ; 
 int /*<<< orphan*/  iput (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct fsync_inode_entry*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void del_fsync_inode(struct fsync_inode_entry *entry, int drop)
{
	if (drop) {
		/* inode should not be recovered, drop it */
		f2fs_inode_synced(entry->inode);
	}
	iput(entry->inode);
	list_del(&entry->list);
	kmem_cache_free(fsync_entry_slab, entry);
}