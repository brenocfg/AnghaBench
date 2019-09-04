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
struct super_block {int /*<<< orphan*/  s_bdev; } ;
struct ocfs2_dinode {int dummy; } ;
struct ocfs2_blockcheck_stats {int /*<<< orphan*/  b_lock; } ;
struct ocfs1_vol_disk_hdr {int /*<<< orphan*/  signature; int /*<<< orphan*/  minor_version; int /*<<< orphan*/  major_version; } ;
struct buffer_head {scalar_t__ b_data; } ;

/* Variables and functions */
 int EAGAIN ; 
 int EINVAL ; 
 int /*<<< orphan*/  ML_ERROR ; 
 int /*<<< orphan*/  OCFS1_MAJOR_VERSION ; 
 int /*<<< orphan*/  OCFS1_VOLUME_SIGNATURE ; 
 int OCFS2_MAX_BLOCKSIZE ; 
 int OCFS2_MIN_BLOCKSIZE ; 
 int /*<<< orphan*/  OCFS2_SUPER_BLOCK_BLKNO ; 
 int bdev_logical_block_size (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brelse (struct buffer_head*) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct ocfs2_blockcheck_stats*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*,...) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int ocfs2_get_sector (struct super_block*,struct buffer_head**,int /*<<< orphan*/ ,int) ; 
 int ocfs2_verify_volume (struct ocfs2_dinode*,struct buffer_head*,int,struct ocfs2_blockcheck_stats*) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  strlen (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ocfs2_sb_probe(struct super_block *sb,
			  struct buffer_head **bh,
			  int *sector_size,
			  struct ocfs2_blockcheck_stats *stats)
{
	int status, tmpstat;
	struct ocfs1_vol_disk_hdr *hdr;
	struct ocfs2_dinode *di;
	int blksize;

	*bh = NULL;

	/* may be > 512 */
	*sector_size = bdev_logical_block_size(sb->s_bdev);
	if (*sector_size > OCFS2_MAX_BLOCKSIZE) {
		mlog(ML_ERROR, "Hardware sector size too large: %d (max=%d)\n",
		     *sector_size, OCFS2_MAX_BLOCKSIZE);
		status = -EINVAL;
		goto bail;
	}

	/* Can this really happen? */
	if (*sector_size < OCFS2_MIN_BLOCKSIZE)
		*sector_size = OCFS2_MIN_BLOCKSIZE;

	/* check block zero for old format */
	status = ocfs2_get_sector(sb, bh, 0, *sector_size);
	if (status < 0) {
		mlog_errno(status);
		goto bail;
	}
	hdr = (struct ocfs1_vol_disk_hdr *) (*bh)->b_data;
	if (hdr->major_version == OCFS1_MAJOR_VERSION) {
		mlog(ML_ERROR, "incompatible version: %u.%u\n",
		     hdr->major_version, hdr->minor_version);
		status = -EINVAL;
	}
	if (memcmp(hdr->signature, OCFS1_VOLUME_SIGNATURE,
		   strlen(OCFS1_VOLUME_SIGNATURE)) == 0) {
		mlog(ML_ERROR, "incompatible volume signature: %8s\n",
		     hdr->signature);
		status = -EINVAL;
	}
	brelse(*bh);
	*bh = NULL;
	if (status < 0) {
		mlog(ML_ERROR, "This is an ocfs v1 filesystem which must be "
		     "upgraded before mounting with ocfs v2\n");
		goto bail;
	}

	/*
	 * Now check at magic offset for 512, 1024, 2048, 4096
	 * blocksizes.  4096 is the maximum blocksize because it is
	 * the minimum clustersize.
	 */
	status = -EINVAL;
	for (blksize = *sector_size;
	     blksize <= OCFS2_MAX_BLOCKSIZE;
	     blksize <<= 1) {
		tmpstat = ocfs2_get_sector(sb, bh,
					   OCFS2_SUPER_BLOCK_BLKNO,
					   blksize);
		if (tmpstat < 0) {
			status = tmpstat;
			mlog_errno(status);
			break;
		}
		di = (struct ocfs2_dinode *) (*bh)->b_data;
		memset(stats, 0, sizeof(struct ocfs2_blockcheck_stats));
		spin_lock_init(&stats->b_lock);
		tmpstat = ocfs2_verify_volume(di, *bh, blksize, stats);
		if (tmpstat < 0) {
			brelse(*bh);
			*bh = NULL;
		}
		if (tmpstat != -EAGAIN) {
			status = tmpstat;
			break;
		}
	}

bail:
	return status;
}