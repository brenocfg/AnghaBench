#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u64 ;
struct ocfs2_xattr_bucket {TYPE_3__* bu_inode; int /*<<< orphan*/  bu_blocks; int /*<<< orphan*/  bu_bhs; } ;
struct TYPE_6__ {int /*<<< orphan*/  i_sb; } ;
struct TYPE_5__ {int /*<<< orphan*/  osb_xattr_lock; } ;
struct TYPE_4__ {int /*<<< orphan*/  xh_check; } ;

/* Variables and functions */
 int /*<<< orphan*/  INODE_CACHE (TYPE_3__*) ; 
 TYPE_2__* OCFS2_SB (int /*<<< orphan*/ ) ; 
 TYPE_1__* bucket_xh (struct ocfs2_xattr_bucket*) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int ocfs2_read_blocks (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int ocfs2_validate_meta_ecc_bhs (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ocfs2_xattr_bucket_relse (struct ocfs2_xattr_bucket*) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ocfs2_read_xattr_bucket(struct ocfs2_xattr_bucket *bucket,
				   u64 xb_blkno)
{
	int rc;

	rc = ocfs2_read_blocks(INODE_CACHE(bucket->bu_inode), xb_blkno,
			       bucket->bu_blocks, bucket->bu_bhs, 0,
			       NULL);
	if (!rc) {
		spin_lock(&OCFS2_SB(bucket->bu_inode->i_sb)->osb_xattr_lock);
		rc = ocfs2_validate_meta_ecc_bhs(bucket->bu_inode->i_sb,
						 bucket->bu_bhs,
						 bucket->bu_blocks,
						 &bucket_xh(bucket)->xh_check);
		spin_unlock(&OCFS2_SB(bucket->bu_inode->i_sb)->osb_xattr_lock);
		if (rc)
			mlog_errno(rc);
	}

	if (rc)
		ocfs2_xattr_bucket_relse(bucket);
	return rc;
}