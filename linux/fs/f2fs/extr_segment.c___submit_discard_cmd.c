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
struct TYPE_3__ {int /*<<< orphan*/  max_discard_sectors; } ;
struct request_queue {TYPE_1__ limits; } ;
struct list_head {int dummy; } ;
struct f2fs_sb_info {int dummy; } ;
struct discard_policy {scalar_t__ type; unsigned int max_requests; scalar_t__ sync; } ;
struct discard_cmd_control {int /*<<< orphan*/  issued_discard; int /*<<< orphan*/  queued_discard; struct list_head wait_list; struct list_head fstrim_list; } ;
struct discard_cmd {scalar_t__ state; unsigned int start; unsigned int len; unsigned int lstart; int /*<<< orphan*/  list; int /*<<< orphan*/  queued; int /*<<< orphan*/  lock; int /*<<< orphan*/  bio_ref; struct block_device* bdev; } ;
struct block_device {int dummy; } ;
struct bio {int bi_opf; int /*<<< orphan*/  bi_end_io; struct discard_cmd* bi_private; } ;
typedef  unsigned int block_t ;
struct TYPE_4__ {struct discard_cmd_control* dcc_info; } ;

/* Variables and functions */
 scalar_t__ DPOLICY_FSTRIM ; 
 scalar_t__ D_PARTIAL ; 
 scalar_t__ D_PREP ; 
 void* D_SUBMIT ; 
 int EIO ; 
 int /*<<< orphan*/  FAULT_DISCARD ; 
 int /*<<< orphan*/  FS_DISCARD ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 int REQ_SYNC ; 
 int /*<<< orphan*/  SBI_NEED_FSCK ; 
 int /*<<< orphan*/  SECTOR_FROM_BLOCK (unsigned int) ; 
 unsigned int SECTOR_TO_BLOCK (int /*<<< orphan*/ ) ; 
 TYPE_2__* SM_I (struct f2fs_sb_info*) ; 
 int __blkdev_issue_discard (struct block_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct bio**) ; 
 int /*<<< orphan*/  __check_sit_bitmap (struct f2fs_sb_info*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  __update_discard_tree_range (struct f2fs_sb_info*,struct block_device*,unsigned int,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 struct request_queue* bdev_get_queue (struct block_device*) ; 
 int /*<<< orphan*/  f2fs_bug_on (struct f2fs_sb_info*,int) ; 
 int /*<<< orphan*/  f2fs_show_injection_info (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  f2fs_submit_discard_endio ; 
 int /*<<< orphan*/  f2fs_update_iostat (struct f2fs_sb_info*,int /*<<< orphan*/ ,int) ; 
 scalar_t__ is_sbi_flag_set (struct f2fs_sb_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_move_tail (int /*<<< orphan*/ *,struct list_head*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  submit_bio (struct bio*) ; 
 scalar_t__ time_to_inject (struct f2fs_sb_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_f2fs_issue_discard (struct block_device*,unsigned int,unsigned int) ; 

__attribute__((used)) static int __submit_discard_cmd(struct f2fs_sb_info *sbi,
						struct discard_policy *dpolicy,
						struct discard_cmd *dc,
						unsigned int *issued)
{
	struct block_device *bdev = dc->bdev;
	struct request_queue *q = bdev_get_queue(bdev);
	unsigned int max_discard_blocks =
			SECTOR_TO_BLOCK(q->limits.max_discard_sectors);
	struct discard_cmd_control *dcc = SM_I(sbi)->dcc_info;
	struct list_head *wait_list = (dpolicy->type == DPOLICY_FSTRIM) ?
					&(dcc->fstrim_list) : &(dcc->wait_list);
	int flag = dpolicy->sync ? REQ_SYNC : 0;
	block_t lstart, start, len, total_len;
	int err = 0;

	if (dc->state != D_PREP)
		return 0;

	if (is_sbi_flag_set(sbi, SBI_NEED_FSCK))
		return 0;

	trace_f2fs_issue_discard(bdev, dc->start, dc->len);

	lstart = dc->lstart;
	start = dc->start;
	len = dc->len;
	total_len = len;

	dc->len = 0;

	while (total_len && *issued < dpolicy->max_requests && !err) {
		struct bio *bio = NULL;
		unsigned long flags;
		bool last = true;

		if (len > max_discard_blocks) {
			len = max_discard_blocks;
			last = false;
		}

		(*issued)++;
		if (*issued == dpolicy->max_requests)
			last = true;

		dc->len += len;

		if (time_to_inject(sbi, FAULT_DISCARD)) {
			f2fs_show_injection_info(FAULT_DISCARD);
			err = -EIO;
			goto submit;
		}
		err = __blkdev_issue_discard(bdev,
					SECTOR_FROM_BLOCK(start),
					SECTOR_FROM_BLOCK(len),
					GFP_NOFS, 0, &bio);
submit:
		if (err) {
			spin_lock_irqsave(&dc->lock, flags);
			if (dc->state == D_PARTIAL)
				dc->state = D_SUBMIT;
			spin_unlock_irqrestore(&dc->lock, flags);

			break;
		}

		f2fs_bug_on(sbi, !bio);

		/*
		 * should keep before submission to avoid D_DONE
		 * right away
		 */
		spin_lock_irqsave(&dc->lock, flags);
		if (last)
			dc->state = D_SUBMIT;
		else
			dc->state = D_PARTIAL;
		dc->bio_ref++;
		spin_unlock_irqrestore(&dc->lock, flags);

		atomic_inc(&dcc->queued_discard);
		dc->queued++;
		list_move_tail(&dc->list, wait_list);

		/* sanity check on discard range */
		__check_sit_bitmap(sbi, lstart, lstart + len);

		bio->bi_private = dc;
		bio->bi_end_io = f2fs_submit_discard_endio;
		bio->bi_opf |= flag;
		submit_bio(bio);

		atomic_inc(&dcc->issued_discard);

		f2fs_update_iostat(sbi, FS_DISCARD, 1);

		lstart += len;
		start += len;
		total_len -= len;
		len = total_len;
	}

	if (!err && len)
		__update_discard_tree_range(sbi, bdev, lstart, start, len);
	return err;
}