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
struct ocfs2_inode_info {int /*<<< orphan*/  ip_alloc_sem; } ;
struct inode {int dummy; } ;
struct buffer_head {int dummy; } ;
typedef  int /*<<< orphan*/  sector_t ;

/* Variables and functions */
 struct ocfs2_inode_info* OCFS2_I (struct inode*) ; 
 int /*<<< orphan*/  down_read (int /*<<< orphan*/ *) ; 
 int ocfs2_get_block (struct inode*,int /*<<< orphan*/ ,struct buffer_head*,int) ; 
 int /*<<< orphan*/  up_read (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int ocfs2_lock_get_block(struct inode *inode, sector_t iblock,
		    struct buffer_head *bh_result, int create)
{
	int ret = 0;
	struct ocfs2_inode_info *oi = OCFS2_I(inode);

	down_read(&oi->ip_alloc_sem);
	ret = ocfs2_get_block(inode, iblock, bh_result, create);
	up_read(&oi->ip_alloc_sem);

	return ret;
}