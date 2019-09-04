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
struct the_nilfs {int ns_blocksize_bits; int /*<<< orphan*/  ns_bdev; } ;
typedef  scalar_t__ sector_t ;
typedef  int /*<<< orphan*/  __u64 ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_NOFS ; 
 int bdev_logical_block_size (int /*<<< orphan*/ ) ; 
 int blkdev_issue_discard (int /*<<< orphan*/ ,scalar_t__,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nilfs_get_segment_range (struct the_nilfs*,int /*<<< orphan*/ ,scalar_t__*,scalar_t__*) ; 

int nilfs_discard_segments(struct the_nilfs *nilfs, __u64 *segnump,
			    size_t nsegs)
{
	sector_t seg_start, seg_end;
	sector_t start = 0, nblocks = 0;
	unsigned int sects_per_block;
	__u64 *sn;
	int ret = 0;

	sects_per_block = (1 << nilfs->ns_blocksize_bits) /
		bdev_logical_block_size(nilfs->ns_bdev);
	for (sn = segnump; sn < segnump + nsegs; sn++) {
		nilfs_get_segment_range(nilfs, *sn, &seg_start, &seg_end);

		if (!nblocks) {
			start = seg_start;
			nblocks = seg_end - seg_start + 1;
		} else if (start + nblocks == seg_start) {
			nblocks += seg_end - seg_start + 1;
		} else {
			ret = blkdev_issue_discard(nilfs->ns_bdev,
						   start * sects_per_block,
						   nblocks * sects_per_block,
						   GFP_NOFS, 0);
			if (ret < 0)
				return ret;
			nblocks = 0;
		}
	}
	if (nblocks)
		ret = blkdev_issue_discard(nilfs->ns_bdev,
					   start * sects_per_block,
					   nblocks * sects_per_block,
					   GFP_NOFS, 0);
	return ret;
}