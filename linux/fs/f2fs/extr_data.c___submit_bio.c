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
struct page {int dummy; } ;
struct f2fs_sb_info {int /*<<< orphan*/  sb; int /*<<< orphan*/  write_io_dummy; } ;
struct TYPE_3__ {unsigned int bi_size; } ;
struct bio {TYPE_1__ bi_iter; } ;
typedef  enum page_type { ____Placeholder_page_type } page_type ;
struct TYPE_4__ {scalar_t__ plug; } ;

/* Variables and functions */
 int DATA ; 
 scalar_t__ DUMMY_WRITTEN_PAGE ; 
 unsigned int F2FS_BLKSIZE_BITS ; 
 scalar_t__ F2FS_IO_ALIGNED (struct f2fs_sb_info*) ; 
 unsigned int F2FS_IO_SIZE (struct f2fs_sb_info*) ; 
 int GFP_NOIO ; 
 int /*<<< orphan*/  LFS ; 
 int NODE ; 
 scalar_t__ PAGE_SIZE ; 
 int /*<<< orphan*/  SBI_NEED_CP ; 
 int /*<<< orphan*/  SetPagePrivate (struct page*) ; 
 int __GFP_NOFAIL ; 
 scalar_t__ bio_add_page (struct bio*,struct page*,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bio_op (struct bio*) ; 
 int /*<<< orphan*/  blk_finish_plug (scalar_t__) ; 
 TYPE_2__* current ; 
 int /*<<< orphan*/  f2fs_bug_on (struct f2fs_sb_info*,int) ; 
 scalar_t__ is_read_io (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  lock_page (struct page*) ; 
 struct page* mempool_alloc (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  set_page_private (struct page*,unsigned long) ; 
 int /*<<< orphan*/  set_sbi_flag (struct f2fs_sb_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  submit_bio (struct bio*) ; 
 scalar_t__ test_opt (struct f2fs_sb_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_f2fs_submit_read_bio (int /*<<< orphan*/ ,int,struct bio*) ; 
 int /*<<< orphan*/  trace_f2fs_submit_write_bio (int /*<<< orphan*/ ,int,struct bio*) ; 
 int /*<<< orphan*/  zero_user_segment (struct page*,int /*<<< orphan*/ ,scalar_t__) ; 

__attribute__((used)) static inline void __submit_bio(struct f2fs_sb_info *sbi,
				struct bio *bio, enum page_type type)
{
	if (!is_read_io(bio_op(bio))) {
		unsigned int start;

		if (type != DATA && type != NODE)
			goto submit_io;

		if (test_opt(sbi, LFS) && current->plug)
			blk_finish_plug(current->plug);

		if (F2FS_IO_ALIGNED(sbi))
			goto submit_io;

		start = bio->bi_iter.bi_size >> F2FS_BLKSIZE_BITS;
		start %= F2FS_IO_SIZE(sbi);

		if (start == 0)
			goto submit_io;

		/* fill dummy pages */
		for (; start < F2FS_IO_SIZE(sbi); start++) {
			struct page *page =
				mempool_alloc(sbi->write_io_dummy,
					      GFP_NOIO | __GFP_NOFAIL);
			f2fs_bug_on(sbi, !page);

			zero_user_segment(page, 0, PAGE_SIZE);
			SetPagePrivate(page);
			set_page_private(page, (unsigned long)DUMMY_WRITTEN_PAGE);
			lock_page(page);
			if (bio_add_page(bio, page, PAGE_SIZE, 0) < PAGE_SIZE)
				f2fs_bug_on(sbi, 1);
		}
		/*
		 * In the NODE case, we lose next block address chain. So, we
		 * need to do checkpoint in f2fs_sync_file.
		 */
		if (type == NODE)
			set_sbi_flag(sbi, SBI_NEED_CP);
	}
submit_io:
	if (is_read_io(bio_op(bio)))
		trace_f2fs_submit_read_bio(sbi->sb, type, bio);
	else
		trace_f2fs_submit_write_bio(sbi->sb, type, bio);
	submit_bio(bio);
}