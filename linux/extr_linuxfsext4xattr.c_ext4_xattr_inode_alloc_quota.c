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
struct inode {int dummy; } ;

/* Variables and functions */
 int dquot_alloc_inode (struct inode*) ; 
 int dquot_alloc_space_nodirty (struct inode*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dquot_free_inode (struct inode*) ; 
 int /*<<< orphan*/  round_up_cluster (struct inode*,size_t) ; 

__attribute__((used)) static int ext4_xattr_inode_alloc_quota(struct inode *inode, size_t len)
{
	int err;

	err = dquot_alloc_inode(inode);
	if (err)
		return err;
	err = dquot_alloc_space_nodirty(inode, round_up_cluster(inode, len));
	if (err)
		dquot_free_inode(inode);
	return err;
}