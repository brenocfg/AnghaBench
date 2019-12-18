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
typedef  int /*<<< orphan*/  u32 ;
struct super_block {int dummy; } ;
struct inode {int dummy; } ;

/* Variables and functions */
 struct inode* ERR_CAST (struct inode*) ; 
 struct inode* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ESTALE ; 
 scalar_t__ IS_ERR (struct inode*) ; 
 struct inode* affs_iget (struct super_block*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  affs_validblock (struct super_block*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct inode *affs_nfs_get_inode(struct super_block *sb, u64 ino,
					u32 generation)
{
	struct inode *inode;

	if (!affs_validblock(sb, ino))
		return ERR_PTR(-ESTALE);

	inode = affs_iget(sb, ino);
	if (IS_ERR(inode))
		return ERR_CAST(inode);

	return inode;
}