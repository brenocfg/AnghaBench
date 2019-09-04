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
typedef  scalar_t__ u64 ;
typedef  unsigned long u32 ;
struct the_nilfs {unsigned long ns_blocks_per_segment; scalar_t__ ns_blocksize_bits; } ;
struct nilfs_segment_summary {int /*<<< orphan*/  ss_datasum; int /*<<< orphan*/  ss_nblocks; int /*<<< orphan*/  ss_seq; int /*<<< orphan*/  ss_magic; } ;
struct buffer_head {int /*<<< orphan*/  b_blocknr; } ;

/* Variables and functions */
 unsigned long NILFS_SEGSUM_MAGIC ; 
 int NILFS_SEG_FAIL_CHECKSUM_FULL ; 
 int NILFS_SEG_FAIL_CONSISTENCY ; 
 int NILFS_SEG_FAIL_IO ; 
 int NILFS_SEG_FAIL_MAGIC ; 
 int NILFS_SEG_FAIL_SEQ ; 
 unsigned long le32_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ le64_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ nilfs_compute_checksum (struct the_nilfs*,struct buffer_head*,unsigned long*,int,scalar_t__,int /*<<< orphan*/ ,unsigned long) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int nilfs_validate_log(struct the_nilfs *nilfs, u64 seg_seq,
			      struct buffer_head *bh_sum,
			      struct nilfs_segment_summary *sum)
{
	unsigned long nblock;
	u32 crc;
	int ret;

	ret = NILFS_SEG_FAIL_MAGIC;
	if (le32_to_cpu(sum->ss_magic) != NILFS_SEGSUM_MAGIC)
		goto out;

	ret = NILFS_SEG_FAIL_SEQ;
	if (le64_to_cpu(sum->ss_seq) != seg_seq)
		goto out;

	nblock = le32_to_cpu(sum->ss_nblocks);
	ret = NILFS_SEG_FAIL_CONSISTENCY;
	if (unlikely(nblock == 0 || nblock > nilfs->ns_blocks_per_segment))
		/* This limits the number of blocks read in the CRC check */
		goto out;

	ret = NILFS_SEG_FAIL_IO;
	if (nilfs_compute_checksum(nilfs, bh_sum, &crc, sizeof(sum->ss_datasum),
				   ((u64)nblock << nilfs->ns_blocksize_bits),
				   bh_sum->b_blocknr, nblock))
		goto out;

	ret = NILFS_SEG_FAIL_CHECKSUM_FULL;
	if (crc != le32_to_cpu(sum->ss_datasum))
		goto out;
	ret = 0;
out:
	return ret;
}