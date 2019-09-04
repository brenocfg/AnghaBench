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
 struct inode* isofs_iget (struct super_block*,unsigned long,unsigned long) ; 

__attribute__((used)) static struct dentry *
isofs_export_iget(struct super_block *sb,
		  unsigned long block,
		  unsigned long offset,
		  __u32 generation)
{
	struct inode *inode;

	if (block == 0)
		return ERR_PTR(-ESTALE);
	inode = isofs_iget(sb, block, offset);
	if (IS_ERR(inode))
		return ERR_CAST(inode);
	if (generation && inode->i_generation != generation) {
		iput(inode);
		return ERR_PTR(-ESTALE);
	}
	return d_obtain_alias(inode);
}