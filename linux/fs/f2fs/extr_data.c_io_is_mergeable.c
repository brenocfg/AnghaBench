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
struct f2fs_io_info {scalar_t__ type; } ;
struct f2fs_bio_info {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  bi_size; } ;
struct bio {unsigned int bi_max_vecs; unsigned int bi_vcnt; TYPE_1__ bi_iter; } ;
typedef  int /*<<< orphan*/  block_t ;

/* Variables and functions */
 scalar_t__ DATA ; 
 unsigned int F2FS_BYTES_TO_BLK (int /*<<< orphan*/ ) ; 
 scalar_t__ F2FS_IO_ALIGNED (struct f2fs_sb_info*) ; 
 unsigned int F2FS_IO_SIZE (struct f2fs_sb_info*) ; 
 scalar_t__ NODE ; 
 int io_type_is_mergeable (struct f2fs_bio_info*,struct f2fs_io_info*) ; 
 int /*<<< orphan*/  page_is_mergeable (struct f2fs_sb_info*,struct bio*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool io_is_mergeable(struct f2fs_sb_info *sbi, struct bio *bio,
					struct f2fs_bio_info *io,
					struct f2fs_io_info *fio,
					block_t last_blkaddr,
					block_t cur_blkaddr)
{
	if (F2FS_IO_ALIGNED(sbi) && (fio->type == DATA || fio->type == NODE)) {
		unsigned int filled_blocks =
				F2FS_BYTES_TO_BLK(bio->bi_iter.bi_size);
		unsigned int io_size = F2FS_IO_SIZE(sbi);
		unsigned int left_vecs = bio->bi_max_vecs - bio->bi_vcnt;

		/* IOs in bio is aligned and left space of vectors is not enough */
		if (!(filled_blocks % io_size) && left_vecs < io_size)
			return false;
	}
	if (!page_is_mergeable(sbi, bio, last_blkaddr, cur_blkaddr))
		return false;
	return io_type_is_mergeable(io, fio);
}