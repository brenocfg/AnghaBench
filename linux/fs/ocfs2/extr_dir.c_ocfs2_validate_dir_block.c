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
struct ocfs2_dir_block_trailer {int /*<<< orphan*/  db_check; } ;
struct buffer_head {scalar_t__ b_blocknr; int /*<<< orphan*/  b_data; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  ML_ERROR ; 
 int /*<<< orphan*/  buffer_uptodate (struct buffer_head*) ; 
 int /*<<< orphan*/  mlog (int /*<<< orphan*/ ,char*,unsigned long long) ; 
 struct ocfs2_dir_block_trailer* ocfs2_trailer_from_bh (struct buffer_head*,struct super_block*) ; 
 int ocfs2_validate_meta_ecc (struct super_block*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_ocfs2_validate_dir_block (unsigned long long) ; 

__attribute__((used)) static int ocfs2_validate_dir_block(struct super_block *sb,
				    struct buffer_head *bh)
{
	int rc;
	struct ocfs2_dir_block_trailer *trailer =
		ocfs2_trailer_from_bh(bh, sb);


	/*
	 * We don't validate dirents here, that's handled
	 * in-place when the code walks them.
	 */
	trace_ocfs2_validate_dir_block((unsigned long long)bh->b_blocknr);

	BUG_ON(!buffer_uptodate(bh));

	/*
	 * If the ecc fails, we return the error but otherwise
	 * leave the filesystem running.  We know any error is
	 * local to this block.
	 *
	 * Note that we are safe to call this even if the directory
	 * doesn't have a trailer.  Filesystems without metaecc will do
	 * nothing, and filesystems with it will have one.
	 */
	rc = ocfs2_validate_meta_ecc(sb, bh->b_data, &trailer->db_check);
	if (rc)
		mlog(ML_ERROR, "Checksum failed for dinode %llu\n",
		     (unsigned long long)bh->b_blocknr);

	return rc;
}