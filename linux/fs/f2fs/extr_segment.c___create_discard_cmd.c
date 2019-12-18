#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct list_head {int dummy; } ;
struct f2fs_sb_info {int dummy; } ;
struct discard_cmd_control {int /*<<< orphan*/  undiscard_blks; int /*<<< orphan*/  discard_cmd_cnt; struct list_head* pend_list; } ;
struct discard_cmd {scalar_t__ bio_ref; int /*<<< orphan*/  lock; int /*<<< orphan*/  list; int /*<<< orphan*/  wait; scalar_t__ error; scalar_t__ queued; int /*<<< orphan*/  state; scalar_t__ ref; void* len; void* start; void* lstart; struct block_device* bdev; } ;
struct block_device {int dummy; } ;
typedef  void* block_t ;
struct TYPE_2__ {struct discard_cmd_control* dcc_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  D_PREP ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 TYPE_1__* SM_I (struct f2fs_sb_info*) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  discard_cmd_slab ; 
 int /*<<< orphan*/  f2fs_bug_on (struct f2fs_sb_info*,int) ; 
 struct discard_cmd* f2fs_kmem_cache_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  init_completion (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,struct list_head*) ; 
 size_t plist_idx (void*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct discard_cmd *__create_discard_cmd(struct f2fs_sb_info *sbi,
		struct block_device *bdev, block_t lstart,
		block_t start, block_t len)
{
	struct discard_cmd_control *dcc = SM_I(sbi)->dcc_info;
	struct list_head *pend_list;
	struct discard_cmd *dc;

	f2fs_bug_on(sbi, !len);

	pend_list = &dcc->pend_list[plist_idx(len)];

	dc = f2fs_kmem_cache_alloc(discard_cmd_slab, GFP_NOFS);
	INIT_LIST_HEAD(&dc->list);
	dc->bdev = bdev;
	dc->lstart = lstart;
	dc->start = start;
	dc->len = len;
	dc->ref = 0;
	dc->state = D_PREP;
	dc->queued = 0;
	dc->error = 0;
	init_completion(&dc->wait);
	list_add_tail(&dc->list, pend_list);
	spin_lock_init(&dc->lock);
	dc->bio_ref = 0;
	atomic_inc(&dcc->discard_cmd_cnt);
	dcc->undiscard_blks += len;

	return dc;
}