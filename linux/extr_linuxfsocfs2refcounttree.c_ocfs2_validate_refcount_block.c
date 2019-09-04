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
struct super_block {int dummy; } ;
struct ocfs2_refcount_block {int /*<<< orphan*/  rf_fs_generation; int /*<<< orphan*/  rf_blkno; int /*<<< orphan*/  rf_signature; int /*<<< orphan*/  rf_check; } ;
struct buffer_head {scalar_t__ b_blocknr; scalar_t__ b_data; } ;
struct TYPE_2__ {unsigned long long fs_generation; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  ML_ERROR ; 
 int /*<<< orphan*/  OCFS2_IS_VALID_REFCOUNT_BLOCK (struct ocfs2_refcount_block*) ; 
 TYPE_1__* OCFS2_SB (struct super_block*) ; 
 int /*<<< orphan*/  buffer_uptodate (struct buffer_head*) ; 
 unsigned long long le32_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ le64_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*,unsigned long long) ; 
 int ocfs2_error (struct super_block*,char*,unsigned long long,unsigned long long,...) ; 
 int ocfs2_validate_meta_ecc (struct super_block*,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_ocfs2_validate_refcount_block (unsigned long long) ; 

__attribute__((used)) static int ocfs2_validate_refcount_block(struct super_block *sb,
					 struct buffer_head *bh)
{
	int rc;
	struct ocfs2_refcount_block *rb =
		(struct ocfs2_refcount_block *)bh->b_data;

	trace_ocfs2_validate_refcount_block((unsigned long long)bh->b_blocknr);

	BUG_ON(!buffer_uptodate(bh));

	/*
	 * If the ecc fails, we return the error but otherwise
	 * leave the filesystem running.  We know any error is
	 * local to this block.
	 */
	rc = ocfs2_validate_meta_ecc(sb, bh->b_data, &rb->rf_check);
	if (rc) {
		mlog(ML_ERROR, "Checksum failed for refcount block %llu\n",
		     (unsigned long long)bh->b_blocknr);
		return rc;
	}


	if (!OCFS2_IS_VALID_REFCOUNT_BLOCK(rb)) {
		rc = ocfs2_error(sb,
				 "Refcount block #%llu has bad signature %.*s\n",
				 (unsigned long long)bh->b_blocknr, 7,
				 rb->rf_signature);
		goto out;
	}

	if (le64_to_cpu(rb->rf_blkno) != bh->b_blocknr) {
		rc = ocfs2_error(sb,
				 "Refcount block #%llu has an invalid rf_blkno of %llu\n",
				 (unsigned long long)bh->b_blocknr,
				 (unsigned long long)le64_to_cpu(rb->rf_blkno));
		goto out;
	}

	if (le32_to_cpu(rb->rf_fs_generation) != OCFS2_SB(sb)->fs_generation) {
		rc = ocfs2_error(sb,
				 "Refcount block #%llu has an invalid rf_fs_generation of #%u\n",
				 (unsigned long long)bh->b_blocknr,
				 le32_to_cpu(rb->rf_fs_generation));
		goto out;
	}
out:
	return rc;
}