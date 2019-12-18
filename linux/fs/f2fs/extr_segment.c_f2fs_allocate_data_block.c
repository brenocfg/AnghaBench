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
struct sit_info {int /*<<< orphan*/  sentry_lock; TYPE_1__* s_ops; } ;
struct page {int dummy; } ;
struct f2fs_summary {int dummy; } ;
struct f2fs_sb_info {struct f2fs_bio_info** write_io; } ;
struct f2fs_io_info {int retry; int in_list; size_t type; int temp; int /*<<< orphan*/  list; } ;
struct f2fs_bio_info {int /*<<< orphan*/  io_lock; int /*<<< orphan*/  io_list; } ;
struct curseg_info {int /*<<< orphan*/  curseg_mutex; } ;
typedef  int /*<<< orphan*/  block_t ;
struct TYPE_4__ {int /*<<< orphan*/  curseg_lock; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* allocate_segment ) (struct f2fs_sb_info*,int,int) ;} ;

/* Variables and functions */
 struct curseg_info* CURSEG_I (struct f2fs_sb_info*,int) ; 
 scalar_t__ F2FS_IO_ALIGNED (struct f2fs_sb_info*) ; 
 scalar_t__ GET_SEGNO (struct f2fs_sb_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 scalar_t__ IS_NODESEG (int) ; 
 int /*<<< orphan*/  NEXT_FREE_BLKADDR (struct f2fs_sb_info*,struct curseg_info*) ; 
 scalar_t__ NULL_SEGNO ; 
 struct sit_info* SIT_I (struct f2fs_sb_info*) ; 
 TYPE_2__* SM_I (struct f2fs_sb_info*) ; 
 int /*<<< orphan*/  __add_sum_entry (struct f2fs_sb_info*,int,struct f2fs_summary*) ; 
 int /*<<< orphan*/  __has_curseg_space (struct f2fs_sb_info*,int) ; 
 int /*<<< orphan*/  __refresh_next_blkoff (struct f2fs_sb_info*,struct curseg_info*) ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  down_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  f2fs_inode_chksum_set (struct f2fs_sb_info*,struct page*) ; 
 int /*<<< orphan*/  f2fs_wait_discard_bio (struct f2fs_sb_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  fill_node_footer_blkaddr (struct page*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  locate_dirty_segment (struct f2fs_sb_info*,scalar_t__) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stat_inc_block_count (struct f2fs_sb_info*,struct curseg_info*) ; 
 int /*<<< orphan*/  stub1 (struct f2fs_sb_info*,int,int) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  up_write (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  update_sit_entry (struct f2fs_sb_info*,int /*<<< orphan*/ ,int) ; 

void f2fs_allocate_data_block(struct f2fs_sb_info *sbi, struct page *page,
		block_t old_blkaddr, block_t *new_blkaddr,
		struct f2fs_summary *sum, int type,
		struct f2fs_io_info *fio, bool add_list)
{
	struct sit_info *sit_i = SIT_I(sbi);
	struct curseg_info *curseg = CURSEG_I(sbi, type);

	down_read(&SM_I(sbi)->curseg_lock);

	mutex_lock(&curseg->curseg_mutex);
	down_write(&sit_i->sentry_lock);

	*new_blkaddr = NEXT_FREE_BLKADDR(sbi, curseg);

	f2fs_wait_discard_bio(sbi, *new_blkaddr);

	/*
	 * __add_sum_entry should be resided under the curseg_mutex
	 * because, this function updates a summary entry in the
	 * current summary block.
	 */
	__add_sum_entry(sbi, type, sum);

	__refresh_next_blkoff(sbi, curseg);

	stat_inc_block_count(sbi, curseg);

	/*
	 * SIT information should be updated before segment allocation,
	 * since SSR needs latest valid block information.
	 */
	update_sit_entry(sbi, *new_blkaddr, 1);
	if (GET_SEGNO(sbi, old_blkaddr) != NULL_SEGNO)
		update_sit_entry(sbi, old_blkaddr, -1);

	if (!__has_curseg_space(sbi, type))
		sit_i->s_ops->allocate_segment(sbi, type, false);

	/*
	 * segment dirty status should be updated after segment allocation,
	 * so we just need to update status only one time after previous
	 * segment being closed.
	 */
	locate_dirty_segment(sbi, GET_SEGNO(sbi, old_blkaddr));
	locate_dirty_segment(sbi, GET_SEGNO(sbi, *new_blkaddr));

	up_write(&sit_i->sentry_lock);

	if (page && IS_NODESEG(type)) {
		fill_node_footer_blkaddr(page, NEXT_FREE_BLKADDR(sbi, curseg));

		f2fs_inode_chksum_set(sbi, page);
	}

	if (F2FS_IO_ALIGNED(sbi))
		fio->retry = false;

	if (add_list) {
		struct f2fs_bio_info *io;

		INIT_LIST_HEAD(&fio->list);
		fio->in_list = true;
		io = sbi->write_io[fio->type] + fio->temp;
		spin_lock(&io->io_lock);
		list_add_tail(&fio->list, &io->io_list);
		spin_unlock(&io->io_lock);
	}

	mutex_unlock(&curseg->curseg_mutex);

	up_read(&SM_I(sbi)->curseg_lock);
}