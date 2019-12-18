#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct super_block {int dummy; } ;
struct TYPE_3__ {int /*<<< orphan*/  rb_node; } ;
struct ext4_group_info {TYPE_1__ bb_free_root; } ;
struct ext4_free_data {int efd_count; int /*<<< orphan*/  efd_group; int /*<<< orphan*/  efd_start_cluster; int /*<<< orphan*/  efd_node; } ;
struct ext4_buddy {int /*<<< orphan*/  bd_bitmap_page; int /*<<< orphan*/  bd_buddy_page; struct ext4_group_info* bd_info; } ;
struct TYPE_4__ {int s_mb_free_pending; int /*<<< orphan*/  s_md_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  DISCARD ; 
 int /*<<< orphan*/  EXT4_MB_GRP_CLEAR_TRIMMED (struct ext4_group_info*) ; 
 TYPE_2__* EXT4_SB (struct super_block*) ; 
 int /*<<< orphan*/  ext4_free_data_cachep ; 
 int /*<<< orphan*/  ext4_lock_group (struct super_block*,int /*<<< orphan*/ ) ; 
 int ext4_mb_load_buddy (struct super_block*,int /*<<< orphan*/ ,struct ext4_buddy*) ; 
 int /*<<< orphan*/  ext4_mb_unload_buddy (struct ext4_buddy*) ; 
 int /*<<< orphan*/  ext4_unlock_group (struct super_block*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct ext4_free_data*) ; 
 int /*<<< orphan*/  mb_debug (int,char*,int,int,...) ; 
 int /*<<< orphan*/  mb_free_blocks (int /*<<< orphan*/ *,struct ext4_buddy*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  put_page (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rb_erase (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  test_opt (struct super_block*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void ext4_free_data_in_buddy(struct super_block *sb,
				    struct ext4_free_data *entry)
{
	struct ext4_buddy e4b;
	struct ext4_group_info *db;
	int err, count = 0, count2 = 0;

	mb_debug(1, "gonna free %u blocks in group %u (0x%p):",
		 entry->efd_count, entry->efd_group, entry);

	err = ext4_mb_load_buddy(sb, entry->efd_group, &e4b);
	/* we expect to find existing buddy because it's pinned */
	BUG_ON(err != 0);

	spin_lock(&EXT4_SB(sb)->s_md_lock);
	EXT4_SB(sb)->s_mb_free_pending -= entry->efd_count;
	spin_unlock(&EXT4_SB(sb)->s_md_lock);

	db = e4b.bd_info;
	/* there are blocks to put in buddy to make them really free */
	count += entry->efd_count;
	count2++;
	ext4_lock_group(sb, entry->efd_group);
	/* Take it out of per group rb tree */
	rb_erase(&entry->efd_node, &(db->bb_free_root));
	mb_free_blocks(NULL, &e4b, entry->efd_start_cluster, entry->efd_count);

	/*
	 * Clear the trimmed flag for the group so that the next
	 * ext4_trim_fs can trim it.
	 * If the volume is mounted with -o discard, online discard
	 * is supported and the free blocks will be trimmed online.
	 */
	if (!test_opt(sb, DISCARD))
		EXT4_MB_GRP_CLEAR_TRIMMED(db);

	if (!db->bb_free_root.rb_node) {
		/* No more items in the per group rb tree
		 * balance refcounts from ext4_mb_free_metadata()
		 */
		put_page(e4b.bd_buddy_page);
		put_page(e4b.bd_bitmap_page);
	}
	ext4_unlock_group(sb, entry->efd_group);
	kmem_cache_free(ext4_free_data_cachep, entry);
	ext4_mb_unload_buddy(&e4b);

	mb_debug(1, "freed %u blocks in %u structures\n", count, count2);
}