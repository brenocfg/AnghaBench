#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct f2fs_summary {int dummy; } ;
struct f2fs_io_info {TYPE_1__* sbi; int /*<<< orphan*/  new_blkaddr; int /*<<< orphan*/  old_blkaddr; scalar_t__ retry; int /*<<< orphan*/  page; } ;
struct TYPE_5__ {int /*<<< orphan*/  io_order_lock; } ;

/* Variables and functions */
 int CURSEG_COLD_DATA ; 
 scalar_t__ GET_SEGNO (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  LFS ; 
 int /*<<< orphan*/  META_MAPPING (TYPE_1__*) ; 
 scalar_t__ NULL_SEGNO ; 
 int __get_segment_type (struct f2fs_io_info*) ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  f2fs_allocate_data_block (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,struct f2fs_summary*,int,struct f2fs_io_info*,int) ; 
 int /*<<< orphan*/  f2fs_submit_page_write (struct f2fs_io_info*) ; 
 int /*<<< orphan*/  invalidate_mapping_pages (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ test_opt (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  update_device_state (struct f2fs_io_info*) ; 

__attribute__((used)) static void do_write_page(struct f2fs_summary *sum, struct f2fs_io_info *fio)
{
	int type = __get_segment_type(fio);
	bool keep_order = (test_opt(fio->sbi, LFS) && type == CURSEG_COLD_DATA);

	if (keep_order)
		down_read(&fio->sbi->io_order_lock);
reallocate:
	f2fs_allocate_data_block(fio->sbi, fio->page, fio->old_blkaddr,
			&fio->new_blkaddr, sum, type, fio, true);
	if (GET_SEGNO(fio->sbi, fio->old_blkaddr) != NULL_SEGNO)
		invalidate_mapping_pages(META_MAPPING(fio->sbi),
					fio->old_blkaddr, fio->old_blkaddr);

	/* writeout dirty page into bdev */
	f2fs_submit_page_write(fio);
	if (fio->retry) {
		fio->old_blkaddr = fio->new_blkaddr;
		goto reallocate;
	}

	update_device_state(fio);

	if (keep_order)
		up_read(&fio->sbi->io_order_lock);
}