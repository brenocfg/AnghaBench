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
struct writeback_control {int dummy; } ;
struct f2fs_sb_info {int dummy; } ;
struct bio {int /*<<< orphan*/  bi_write_hint; struct f2fs_sb_info* bi_private; int /*<<< orphan*/  bi_end_io; } ;
typedef  enum temp_type { ____Placeholder_temp_type } temp_type ;
typedef  enum page_type { ____Placeholder_page_type } page_type ;
typedef  int /*<<< orphan*/  block_t ;

/* Variables and functions */
 struct bio* f2fs_bio_alloc (struct f2fs_sb_info*,int,int) ; 
 int /*<<< orphan*/  f2fs_io_type_to_rw_hint (struct f2fs_sb_info*,int,int) ; 
 int /*<<< orphan*/  f2fs_read_end_io ; 
 int /*<<< orphan*/  f2fs_target_device (struct f2fs_sb_info*,int /*<<< orphan*/ ,struct bio*) ; 
 int /*<<< orphan*/  f2fs_write_end_io ; 
 int /*<<< orphan*/  wbc_init_bio (struct writeback_control*,struct bio*) ; 

__attribute__((used)) static struct bio *__bio_alloc(struct f2fs_sb_info *sbi, block_t blk_addr,
				struct writeback_control *wbc,
				int npages, bool is_read,
				enum page_type type, enum temp_type temp)
{
	struct bio *bio;

	bio = f2fs_bio_alloc(sbi, npages, true);

	f2fs_target_device(sbi, blk_addr, bio);
	if (is_read) {
		bio->bi_end_io = f2fs_read_end_io;
		bio->bi_private = NULL;
	} else {
		bio->bi_end_io = f2fs_write_end_io;
		bio->bi_private = sbi;
		bio->bi_write_hint = f2fs_io_type_to_rw_hint(sbi, type, temp);
	}
	if (wbc)
		wbc_init_bio(wbc, bio);

	return bio;
}