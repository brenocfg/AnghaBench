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
struct inode {int dummy; } ;
struct buffer_head {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  INODE_CACHE (struct inode*) ; 
 int ocfs2_read_block (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct buffer_head**,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ocfs2_validate_xattr_block ; 

__attribute__((used)) static int ocfs2_read_xattr_block(struct inode *inode, u64 xb_blkno,
				  struct buffer_head **bh)
{
	int rc;
	struct buffer_head *tmp = *bh;

	rc = ocfs2_read_block(INODE_CACHE(inode), xb_blkno, &tmp,
			      ocfs2_validate_xattr_block);

	/* If ocfs2_read_block() got us a new bh, pass it up. */
	if (!rc && !*bh)
		*bh = tmp;

	return rc;
}