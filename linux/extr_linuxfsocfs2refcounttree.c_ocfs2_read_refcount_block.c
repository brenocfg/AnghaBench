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
typedef  int /*<<< orphan*/  u64 ;
struct ocfs2_caching_info {int dummy; } ;
struct buffer_head {int dummy; } ;

/* Variables and functions */
 int ocfs2_read_block (struct ocfs2_caching_info*,int /*<<< orphan*/ ,struct buffer_head**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocfs2_validate_refcount_block ; 

__attribute__((used)) static int ocfs2_read_refcount_block(struct ocfs2_caching_info *ci,
				     u64 rb_blkno,
				     struct buffer_head **bh)
{
	int rc;
	struct buffer_head *tmp = *bh;

	rc = ocfs2_read_block(ci, rb_blkno, &tmp,
			      ocfs2_validate_refcount_block);

	/* If ocfs2_read_block() got us a new bh, pass it up. */
	if (!rc && !*bh)
		*bh = tmp;

	return rc;
}