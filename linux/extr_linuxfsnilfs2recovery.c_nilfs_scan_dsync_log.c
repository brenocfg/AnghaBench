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
struct the_nilfs {int /*<<< orphan*/  ns_blocksize; int /*<<< orphan*/  ns_bdev; } ;
struct nilfs_segment_summary {int /*<<< orphan*/  ss_bytes; int /*<<< orphan*/  ss_sumbytes; int /*<<< orphan*/  ss_nfinfo; } ;
struct nilfs_recovery_block {int /*<<< orphan*/  list; void* blkoff; void* vblocknr; scalar_t__ blocknr; void* ino; } ;
struct nilfs_finfo {int /*<<< orphan*/  fi_ndatablk; int /*<<< orphan*/  fi_nblocks; int /*<<< orphan*/  fi_ino; } ;
struct nilfs_binfo_v {int /*<<< orphan*/  bi_blkoff; int /*<<< orphan*/  bi_vblocknr; } ;
struct list_head {int dummy; } ;
struct buffer_head {int dummy; } ;
typedef  scalar_t__ sector_t ;
typedef  void* ino_t ;
typedef  int /*<<< orphan*/  __le64 ;

/* Variables and functions */
 scalar_t__ DIV_ROUND_UP (scalar_t__,int /*<<< orphan*/ ) ; 
 int EIO ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_NOFS ; 
 struct buffer_head* __bread (int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 struct nilfs_recovery_block* kmalloc (int,int /*<<< orphan*/ ) ; 
 unsigned int le16_to_cpu (int /*<<< orphan*/ ) ; 
 void* le32_to_cpu (int /*<<< orphan*/ ) ; 
 void* le64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add_tail (int /*<<< orphan*/ *,struct list_head*) ; 
 void* nilfs_read_summary_info (struct the_nilfs*,struct buffer_head**,unsigned int*,int) ; 
 int /*<<< orphan*/  nilfs_skip_summary_info (struct the_nilfs*,struct buffer_head**,unsigned int*,int,unsigned long) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int nilfs_scan_dsync_log(struct the_nilfs *nilfs, sector_t start_blocknr,
				struct nilfs_segment_summary *sum,
				struct list_head *head)
{
	struct buffer_head *bh;
	unsigned int offset;
	u32 nfinfo, sumbytes;
	sector_t blocknr;
	ino_t ino;
	int err = -EIO;

	nfinfo = le32_to_cpu(sum->ss_nfinfo);
	if (!nfinfo)
		return 0;

	sumbytes = le32_to_cpu(sum->ss_sumbytes);
	blocknr = start_blocknr + DIV_ROUND_UP(sumbytes, nilfs->ns_blocksize);
	bh = __bread(nilfs->ns_bdev, start_blocknr, nilfs->ns_blocksize);
	if (unlikely(!bh))
		goto out;

	offset = le16_to_cpu(sum->ss_bytes);
	for (;;) {
		unsigned long nblocks, ndatablk, nnodeblk;
		struct nilfs_finfo *finfo;

		finfo = nilfs_read_summary_info(nilfs, &bh, &offset,
						sizeof(*finfo));
		if (unlikely(!finfo))
			goto out;

		ino = le64_to_cpu(finfo->fi_ino);
		nblocks = le32_to_cpu(finfo->fi_nblocks);
		ndatablk = le32_to_cpu(finfo->fi_ndatablk);
		nnodeblk = nblocks - ndatablk;

		while (ndatablk-- > 0) {
			struct nilfs_recovery_block *rb;
			struct nilfs_binfo_v *binfo;

			binfo = nilfs_read_summary_info(nilfs, &bh, &offset,
							sizeof(*binfo));
			if (unlikely(!binfo))
				goto out;

			rb = kmalloc(sizeof(*rb), GFP_NOFS);
			if (unlikely(!rb)) {
				err = -ENOMEM;
				goto out;
			}
			rb->ino = ino;
			rb->blocknr = blocknr++;
			rb->vblocknr = le64_to_cpu(binfo->bi_vblocknr);
			rb->blkoff = le64_to_cpu(binfo->bi_blkoff);
			/* INIT_LIST_HEAD(&rb->list); */
			list_add_tail(&rb->list, head);
		}
		if (--nfinfo == 0)
			break;
		blocknr += nnodeblk; /* always 0 for data sync logs */
		nilfs_skip_summary_info(nilfs, &bh, &offset, sizeof(__le64),
					nnodeblk);
		if (unlikely(!bh))
			goto out;
	}
	err = 0;
 out:
	brelse(bh);   /* brelse(NULL) is just ignored */
	return err;
}