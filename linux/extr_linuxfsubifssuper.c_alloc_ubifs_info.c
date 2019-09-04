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
struct TYPE_2__ {int /*<<< orphan*/  ubi_num; } ;
struct ubifs_info {int no_chk_data_crc; int /*<<< orphan*/  di; TYPE_1__ vi; int /*<<< orphan*/  ltail_lnum; int /*<<< orphan*/  lhead_lnum; int /*<<< orphan*/  highest_inum; int /*<<< orphan*/  assert_action; int /*<<< orphan*/  orph_new; int /*<<< orphan*/  orph_list; int /*<<< orphan*/  old_buds; int /*<<< orphan*/  unclean_leb_list; int /*<<< orphan*/  frdi_idx_list; int /*<<< orphan*/  freeable_list; int /*<<< orphan*/  empty_list; int /*<<< orphan*/  uncat_list; int /*<<< orphan*/  replay_buds; int /*<<< orphan*/  replay_list; int /*<<< orphan*/  idx_gc; int /*<<< orphan*/  infos_list; void* orph_tree; void* size_tree; void* old_idx; void* buds; int /*<<< orphan*/  cmt_wq; int /*<<< orphan*/  write_reserve_mutex; int /*<<< orphan*/  bu_mutex; int /*<<< orphan*/  umount_mutex; int /*<<< orphan*/  log_mutex; int /*<<< orphan*/  tnc_mutex; int /*<<< orphan*/  lp_mutex; int /*<<< orphan*/  commit_sem; int /*<<< orphan*/  orphan_lock; int /*<<< orphan*/  space_lock; int /*<<< orphan*/  buds_lock; int /*<<< orphan*/  cs_lock; int /*<<< orphan*/  cnt_lock; } ;
struct ubi_volume_desc {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSACT_RO ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 void* RB_ROOT ; 
 int /*<<< orphan*/  UBIFS_FIRST_INO ; 
 int /*<<< orphan*/  UBIFS_LOG_LNUM ; 
 int /*<<< orphan*/  init_rwsem (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 struct ubifs_info* kzalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ubi_get_device_info (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ubi_get_volume_info (struct ubi_volume_desc*,TYPE_1__*) ; 

__attribute__((used)) static struct ubifs_info *alloc_ubifs_info(struct ubi_volume_desc *ubi)
{
	struct ubifs_info *c;

	c = kzalloc(sizeof(struct ubifs_info), GFP_KERNEL);
	if (c) {
		spin_lock_init(&c->cnt_lock);
		spin_lock_init(&c->cs_lock);
		spin_lock_init(&c->buds_lock);
		spin_lock_init(&c->space_lock);
		spin_lock_init(&c->orphan_lock);
		init_rwsem(&c->commit_sem);
		mutex_init(&c->lp_mutex);
		mutex_init(&c->tnc_mutex);
		mutex_init(&c->log_mutex);
		mutex_init(&c->umount_mutex);
		mutex_init(&c->bu_mutex);
		mutex_init(&c->write_reserve_mutex);
		init_waitqueue_head(&c->cmt_wq);
		c->buds = RB_ROOT;
		c->old_idx = RB_ROOT;
		c->size_tree = RB_ROOT;
		c->orph_tree = RB_ROOT;
		INIT_LIST_HEAD(&c->infos_list);
		INIT_LIST_HEAD(&c->idx_gc);
		INIT_LIST_HEAD(&c->replay_list);
		INIT_LIST_HEAD(&c->replay_buds);
		INIT_LIST_HEAD(&c->uncat_list);
		INIT_LIST_HEAD(&c->empty_list);
		INIT_LIST_HEAD(&c->freeable_list);
		INIT_LIST_HEAD(&c->frdi_idx_list);
		INIT_LIST_HEAD(&c->unclean_leb_list);
		INIT_LIST_HEAD(&c->old_buds);
		INIT_LIST_HEAD(&c->orph_list);
		INIT_LIST_HEAD(&c->orph_new);
		c->no_chk_data_crc = 1;
		c->assert_action = ASSACT_RO;

		c->highest_inum = UBIFS_FIRST_INO;
		c->lhead_lnum = c->ltail_lnum = UBIFS_LOG_LNUM;

		ubi_get_volume_info(ubi, &c->vi);
		ubi_get_device_info(c->vi.ubi_num, &c->di);
	}
	return c;
}