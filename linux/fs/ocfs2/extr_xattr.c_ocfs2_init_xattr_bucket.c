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
typedef  scalar_t__ u64 ;
struct ocfs2_xattr_bucket {int bu_blocks; int /*<<< orphan*/ * bu_bhs; TYPE_1__* bu_inode; } ;
struct TYPE_2__ {int /*<<< orphan*/  i_sb; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  INODE_CACHE (TYPE_1__*) ; 
 int /*<<< orphan*/  mlog_errno (int) ; 
 int /*<<< orphan*/  ocfs2_buffer_uptodate (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocfs2_set_buffer_uptodate (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocfs2_set_new_buffer_uptodate (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocfs2_xattr_bucket_relse (struct ocfs2_xattr_bucket*) ; 
 int /*<<< orphan*/  sb_getblk (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  set_buffer_uptodate (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int ocfs2_init_xattr_bucket(struct ocfs2_xattr_bucket *bucket,
				   u64 xb_blkno, int new)
{
	int i, rc = 0;

	for (i = 0; i < bucket->bu_blocks; i++) {
		bucket->bu_bhs[i] = sb_getblk(bucket->bu_inode->i_sb,
					      xb_blkno + i);
		if (!bucket->bu_bhs[i]) {
			rc = -ENOMEM;
			mlog_errno(rc);
			break;
		}

		if (!ocfs2_buffer_uptodate(INODE_CACHE(bucket->bu_inode),
					   bucket->bu_bhs[i])) {
			if (new)
				ocfs2_set_new_buffer_uptodate(INODE_CACHE(bucket->bu_inode),
							      bucket->bu_bhs[i]);
			else {
				set_buffer_uptodate(bucket->bu_bhs[i]);
				ocfs2_set_buffer_uptodate(INODE_CACHE(bucket->bu_inode),
							  bucket->bu_bhs[i]);
			}
		}
	}

	if (rc)
		ocfs2_xattr_bucket_relse(bucket);
	return rc;
}