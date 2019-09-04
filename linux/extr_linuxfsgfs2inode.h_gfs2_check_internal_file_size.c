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
typedef  int u64 ;
struct inode {int /*<<< orphan*/  i_blkbits; } ;

/* Variables and functions */
 int BIT (int /*<<< orphan*/ ) ; 
 int EIO ; 
 int /*<<< orphan*/  GFS2_I (struct inode*) ; 
 int /*<<< orphan*/  gfs2_consist_inode (int /*<<< orphan*/ ) ; 
 int i_size_read (struct inode*) ; 

__attribute__((used)) static inline int gfs2_check_internal_file_size(struct inode *inode,
						u64 minsize, u64 maxsize)
{
	u64 size = i_size_read(inode);
	if (size < minsize || size > maxsize)
		goto err;
	if (size & (BIT(inode->i_blkbits) - 1))
		goto err;
	return 0;
err:
	gfs2_consist_inode(GFS2_I(inode));
	return -EIO;
}