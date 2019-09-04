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
struct fsync_node_entry {unsigned int seq_id; int /*<<< orphan*/  list; struct page* page; } ;
struct f2fs_sb_info {int /*<<< orphan*/  fsync_node_lock; int /*<<< orphan*/  fsync_node_num; int /*<<< orphan*/  fsync_seg_id; int /*<<< orphan*/  fsync_node_list; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_NOFS ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 struct fsync_node_entry* f2fs_kmem_cache_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fsync_node_entry_slab ; 
 int /*<<< orphan*/  get_page (struct page*) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static unsigned int f2fs_add_fsync_node_entry(struct f2fs_sb_info *sbi,
							struct page *page)
{
	struct fsync_node_entry *fn;
	unsigned long flags;
	unsigned int seq_id;

	fn = f2fs_kmem_cache_alloc(fsync_node_entry_slab, GFP_NOFS);

	get_page(page);
	fn->page = page;
	INIT_LIST_HEAD(&fn->list);

	spin_lock_irqsave(&sbi->fsync_node_lock, flags);
	list_add_tail(&fn->list, &sbi->fsync_node_list);
	fn->seq_id = sbi->fsync_seg_id++;
	seq_id = fn->seq_id;
	sbi->fsync_node_num++;
	spin_unlock_irqrestore(&sbi->fsync_node_lock, flags);

	return seq_id;
}