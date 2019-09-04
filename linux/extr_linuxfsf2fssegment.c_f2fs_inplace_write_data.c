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
struct f2fs_sb_info {int dummy; } ;
struct f2fs_io_info {int /*<<< orphan*/  io_type; struct f2fs_sb_info* sbi; int /*<<< orphan*/  new_blkaddr; int /*<<< orphan*/  old_blkaddr; } ;
struct TYPE_2__ {int /*<<< orphan*/  type; } ;

/* Variables and functions */
 int /*<<< orphan*/  F2FS_BLKSIZE ; 
 int /*<<< orphan*/  GET_SEGNO (struct f2fs_sb_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  IS_DATASEG (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  __get_segment_type (struct f2fs_io_info*) ; 
 int /*<<< orphan*/  f2fs_bug_on (struct f2fs_sb_info*,int) ; 
 int f2fs_submit_page_bio (struct f2fs_io_info*) ; 
 int /*<<< orphan*/  f2fs_update_iostat (struct f2fs_sb_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 TYPE_1__* get_seg_entry (struct f2fs_sb_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stat_inc_inplace_blocks (struct f2fs_sb_info*) ; 
 int /*<<< orphan*/  update_device_state (struct f2fs_io_info*) ; 

int f2fs_inplace_write_data(struct f2fs_io_info *fio)
{
	int err;
	struct f2fs_sb_info *sbi = fio->sbi;

	fio->new_blkaddr = fio->old_blkaddr;
	/* i/o temperature is needed for passing down write hints */
	__get_segment_type(fio);

	f2fs_bug_on(sbi, !IS_DATASEG(get_seg_entry(sbi,
			GET_SEGNO(sbi, fio->new_blkaddr))->type));

	stat_inc_inplace_blocks(fio->sbi);

	err = f2fs_submit_page_bio(fio);
	if (!err)
		update_device_state(fio);

	f2fs_update_iostat(fio->sbi, fio->io_type, F2FS_BLKSIZE);

	return err;
}