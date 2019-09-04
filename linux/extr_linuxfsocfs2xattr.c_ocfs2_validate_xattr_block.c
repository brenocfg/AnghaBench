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
struct ocfs2_xattr_block {int /*<<< orphan*/  xb_fs_generation; int /*<<< orphan*/  xb_blkno; int /*<<< orphan*/  xb_signature; int /*<<< orphan*/  xb_check; } ;
struct buffer_head {scalar_t__ b_blocknr; scalar_t__ b_data; } ;
struct TYPE_2__ {unsigned long long fs_generation; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  OCFS2_IS_VALID_XATTR_BLOCK (struct ocfs2_xattr_block*) ; 
 TYPE_1__* OCFS2_SB (struct super_block*) ; 
 int /*<<< orphan*/  buffer_uptodate (struct buffer_head*) ; 
 unsigned long long le32_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ le64_to_cpu (int /*<<< orphan*/ ) ; 
 int ocfs2_error (struct super_block*,char*,unsigned long long,unsigned long long,...) ; 
 int ocfs2_validate_meta_ecc (struct super_block*,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_ocfs2_validate_xattr_block (unsigned long long) ; 

__attribute__((used)) static int ocfs2_validate_xattr_block(struct super_block *sb,
				      struct buffer_head *bh)
{
	int rc;
	struct ocfs2_xattr_block *xb =
		(struct ocfs2_xattr_block *)bh->b_data;

	trace_ocfs2_validate_xattr_block((unsigned long long)bh->b_blocknr);

	BUG_ON(!buffer_uptodate(bh));

	/*
	 * If the ecc fails, we return the error but otherwise
	 * leave the filesystem running.  We know any error is
	 * local to this block.
	 */
	rc = ocfs2_validate_meta_ecc(sb, bh->b_data, &xb->xb_check);
	if (rc)
		return rc;

	/*
	 * Errors after here are fatal
	 */

	if (!OCFS2_IS_VALID_XATTR_BLOCK(xb)) {
		return ocfs2_error(sb,
				   "Extended attribute block #%llu has bad signature %.*s\n",
				   (unsigned long long)bh->b_blocknr, 7,
				   xb->xb_signature);
	}

	if (le64_to_cpu(xb->xb_blkno) != bh->b_blocknr) {
		return ocfs2_error(sb,
				   "Extended attribute block #%llu has an invalid xb_blkno of %llu\n",
				   (unsigned long long)bh->b_blocknr,
				   (unsigned long long)le64_to_cpu(xb->xb_blkno));
	}

	if (le32_to_cpu(xb->xb_fs_generation) != OCFS2_SB(sb)->fs_generation) {
		return ocfs2_error(sb,
				   "Extended attribute block #%llu has an invalid xb_fs_generation of #%u\n",
				   (unsigned long long)bh->b_blocknr,
				   le32_to_cpu(xb->xb_fs_generation));
	}

	return 0;
}