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
typedef  scalar_t__ u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct super_block {int dummy; } ;
struct kernel_lb_addr {int /*<<< orphan*/  partitionReferenceNum; scalar_t__ logicalBlockNum; } ;
struct inode {scalar_t__ i_generation; } ;
struct dentry {int dummy; } ;
typedef  scalar_t__ __u32 ;

/* Variables and functions */
 struct dentry* ERR_CAST (struct inode*) ; 
 struct dentry* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ESTALE ; 
 scalar_t__ IS_ERR (struct inode*) ; 
 struct dentry* d_obtain_alias (struct inode*) ; 
 int /*<<< orphan*/  iput (struct inode*) ; 
 struct inode* udf_iget (struct super_block*,struct kernel_lb_addr*) ; 

__attribute__((used)) static struct dentry *udf_nfs_get_inode(struct super_block *sb, u32 block,
					u16 partref, __u32 generation)
{
	struct inode *inode;
	struct kernel_lb_addr loc;

	if (block == 0)
		return ERR_PTR(-ESTALE);

	loc.logicalBlockNum = block;
	loc.partitionReferenceNum = partref;
	inode = udf_iget(sb, &loc);

	if (IS_ERR(inode))
		return ERR_CAST(inode);

	if (generation && inode->i_generation != generation) {
		iput(inode);
		return ERR_PTR(-ESTALE);
	}
	return d_obtain_alias(inode);
}