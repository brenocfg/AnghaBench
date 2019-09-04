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
typedef  scalar_t__ u32 ;
struct the_nilfs {unsigned int ns_blocksize; int /*<<< orphan*/  ns_sb; int /*<<< orphan*/  ns_bdev; } ;
struct nilfs_super_root {int /*<<< orphan*/  sr_sum; int /*<<< orphan*/  sr_bytes; } ;
struct buffer_head {scalar_t__ b_data; } ;
typedef  int /*<<< orphan*/  sector_t ;

/* Variables and functions */
 int NILFS_SEG_FAIL_CHECKSUM_SUPER_ROOT ; 
 int NILFS_SEG_FAIL_IO ; 
 struct buffer_head* __bread (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 unsigned int le16_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ le32_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ nilfs_compute_checksum (struct the_nilfs*,struct buffer_head*,scalar_t__*,int,unsigned int,int /*<<< orphan*/ ,int) ; 
 int nilfs_warn_segment_error (int /*<<< orphan*/ ,int) ; 
 scalar_t__ unlikely (int) ; 

int nilfs_read_super_root_block(struct the_nilfs *nilfs, sector_t sr_block,
				struct buffer_head **pbh, int check)
{
	struct buffer_head *bh_sr;
	struct nilfs_super_root *sr;
	u32 crc;
	int ret;

	*pbh = NULL;
	bh_sr = __bread(nilfs->ns_bdev, sr_block, nilfs->ns_blocksize);
	if (unlikely(!bh_sr)) {
		ret = NILFS_SEG_FAIL_IO;
		goto failed;
	}

	sr = (struct nilfs_super_root *)bh_sr->b_data;
	if (check) {
		unsigned int bytes = le16_to_cpu(sr->sr_bytes);

		if (bytes == 0 || bytes > nilfs->ns_blocksize) {
			ret = NILFS_SEG_FAIL_CHECKSUM_SUPER_ROOT;
			goto failed_bh;
		}
		if (nilfs_compute_checksum(
			    nilfs, bh_sr, &crc, sizeof(sr->sr_sum), bytes,
			    sr_block, 1)) {
			ret = NILFS_SEG_FAIL_IO;
			goto failed_bh;
		}
		if (crc != le32_to_cpu(sr->sr_sum)) {
			ret = NILFS_SEG_FAIL_CHECKSUM_SUPER_ROOT;
			goto failed_bh;
		}
	}
	*pbh = bh_sr;
	return 0;

 failed_bh:
	brelse(bh_sr);

 failed:
	return nilfs_warn_segment_error(nilfs->ns_sb, ret);
}