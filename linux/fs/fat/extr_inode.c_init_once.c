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
struct msdos_inode_info {int /*<<< orphan*/  vfs_inode; int /*<<< orphan*/  i_dir_hash; int /*<<< orphan*/  i_fat_hash; int /*<<< orphan*/  cache_lru; scalar_t__ cache_valid_id; scalar_t__ nr_caches; int /*<<< orphan*/  cache_lru_lock; } ;

/* Variables and functions */
 scalar_t__ FAT_CACHE_VALID ; 
 int /*<<< orphan*/  INIT_HLIST_NODE (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  inode_init_once (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void init_once(void *foo)
{
	struct msdos_inode_info *ei = (struct msdos_inode_info *)foo;

	spin_lock_init(&ei->cache_lru_lock);
	ei->nr_caches = 0;
	ei->cache_valid_id = FAT_CACHE_VALID + 1;
	INIT_LIST_HEAD(&ei->cache_lru);
	INIT_HLIST_NODE(&ei->i_fat_hash);
	INIT_HLIST_NODE(&ei->i_dir_hash);
	inode_init_once(&ei->vfs_inode);
}