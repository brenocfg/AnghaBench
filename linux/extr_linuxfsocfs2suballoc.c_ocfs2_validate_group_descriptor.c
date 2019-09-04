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
struct ocfs2_group_desc {int /*<<< orphan*/  bg_check; } ;
struct buffer_head {scalar_t__ b_data; scalar_t__ b_blocknr; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  buffer_uptodate (struct buffer_head*) ; 
 int ocfs2_validate_gd_self (struct super_block*,struct buffer_head*,int /*<<< orphan*/ ) ; 
 int ocfs2_validate_meta_ecc (struct super_block*,scalar_t__,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_ocfs2_validate_group_descriptor (unsigned long long) ; 

__attribute__((used)) static int ocfs2_validate_group_descriptor(struct super_block *sb,
					   struct buffer_head *bh)
{
	int rc;
	struct ocfs2_group_desc *gd = (struct ocfs2_group_desc *)bh->b_data;

	trace_ocfs2_validate_group_descriptor(
					(unsigned long long)bh->b_blocknr);

	BUG_ON(!buffer_uptodate(bh));

	/*
	 * If the ecc fails, we return the error but otherwise
	 * leave the filesystem running.  We know any error is
	 * local to this block.
	 */
	rc = ocfs2_validate_meta_ecc(sb, bh->b_data, &gd->bg_check);
	if (rc)
		return rc;

	/*
	 * Errors after here are fatal.
	 */

	return ocfs2_validate_gd_self(sb, bh, 0);
}