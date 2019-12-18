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
struct super_block {int dummy; } ;
struct ocfs2_dx_root_block {int /*<<< orphan*/  dr_signature; int /*<<< orphan*/  dr_blkno; int /*<<< orphan*/  dr_check; } ;
struct buffer_head {scalar_t__ b_blocknr; scalar_t__ b_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  ML_ERROR ; 
 int /*<<< orphan*/  OCFS2_IS_VALID_DX_ROOT (struct ocfs2_dx_root_block*) ; 
 int /*<<< orphan*/  buffer_uptodate (struct buffer_head*) ; 
 scalar_t__ le64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*,unsigned long long) ; 
 int ocfs2_error (struct super_block*,char*,unsigned long long,int,int /*<<< orphan*/ ) ; 
 int ocfs2_validate_meta_ecc (struct super_block*,scalar_t__,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ocfs2_validate_dx_root(struct super_block *sb,
				  struct buffer_head *bh)
{
	int ret;
	struct ocfs2_dx_root_block *dx_root;

	BUG_ON(!buffer_uptodate(bh));

	dx_root = (struct ocfs2_dx_root_block *) bh->b_data;

	ret = ocfs2_validate_meta_ecc(sb, bh->b_data, &dx_root->dr_check);
	if (ret) {
		mlog(ML_ERROR,
		     "Checksum failed for dir index root block %llu\n",
		     (unsigned long long)bh->b_blocknr);
		return ret;
	}

	if (!OCFS2_IS_VALID_DX_ROOT(dx_root)) {
		ret = ocfs2_error(sb,
				  "Dir Index Root # %llu has bad signature %.*s\n",
				  (unsigned long long)le64_to_cpu(dx_root->dr_blkno),
				  7, dx_root->dr_signature);
	}

	return ret;
}