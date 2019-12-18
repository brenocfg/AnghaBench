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
typedef  scalar_t__ u64 ;
struct inode {scalar_t__ i_size; int /*<<< orphan*/  i_mode; } ;
struct gfs2_inode {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 struct gfs2_inode* GFS2_I (struct inode*) ; 
 int /*<<< orphan*/  S_ISREG (int /*<<< orphan*/ ) ; 
 int do_grow (struct inode*,scalar_t__) ; 
 int do_shrink (struct inode*,scalar_t__) ; 
 int gfs2_rsqa_alloc (struct gfs2_inode*) ; 
 int /*<<< orphan*/  gfs2_rsqa_delete (struct gfs2_inode*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  inode_dio_wait (struct inode*) ; 
 int inode_newsize_ok (struct inode*,scalar_t__) ; 

int gfs2_setattr_size(struct inode *inode, u64 newsize)
{
	struct gfs2_inode *ip = GFS2_I(inode);
	int ret;

	BUG_ON(!S_ISREG(inode->i_mode));

	ret = inode_newsize_ok(inode, newsize);
	if (ret)
		return ret;

	inode_dio_wait(inode);

	ret = gfs2_rsqa_alloc(ip);
	if (ret)
		goto out;

	if (newsize >= inode->i_size) {
		ret = do_grow(inode, newsize);
		goto out;
	}

	ret = do_shrink(inode, newsize);
out:
	gfs2_rsqa_delete(ip, NULL);
	return ret;
}