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
struct ocfs2_xattr_bucket {int bu_blocks; int /*<<< orphan*/ * bu_bhs; TYPE_1__* bu_inode; } ;
typedef  int /*<<< orphan*/  handle_t ;
struct TYPE_6__ {int /*<<< orphan*/  osb_xattr_lock; } ;
struct TYPE_5__ {int /*<<< orphan*/  xh_check; } ;
struct TYPE_4__ {int /*<<< orphan*/  i_sb; } ;

/* Variables and functions */
 TYPE_3__* OCFS2_SB (int /*<<< orphan*/ ) ; 
 TYPE_2__* bucket_xh (struct ocfs2_xattr_bucket*) ; 
 int /*<<< orphan*/  ocfs2_compute_meta_ecc_bhs (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ocfs2_journal_dirty (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ocfs2_xattr_bucket_journal_dirty(handle_t *handle,
					     struct ocfs2_xattr_bucket *bucket)
{
	int i;

	spin_lock(&OCFS2_SB(bucket->bu_inode->i_sb)->osb_xattr_lock);
	ocfs2_compute_meta_ecc_bhs(bucket->bu_inode->i_sb,
				   bucket->bu_bhs, bucket->bu_blocks,
				   &bucket_xh(bucket)->xh_check);
	spin_unlock(&OCFS2_SB(bucket->bu_inode->i_sb)->osb_xattr_lock);

	for (i = 0; i < bucket->bu_blocks; i++)
		ocfs2_journal_dirty(handle, bucket->bu_bhs[i]);
}