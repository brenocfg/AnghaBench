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
struct super_block {int dummy; } ;
struct inode {int dummy; } ;

/* Variables and functions */
 struct inode* iget5_locked (struct super_block*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  iget_set ; 
 int /*<<< orphan*/  iget_test ; 
 int /*<<< orphan*/  iput (struct inode*) ; 
 scalar_t__ is_bad_inode (struct inode*) ; 

__attribute__((used)) static struct inode *gfs2_iget(struct super_block *sb, u64 no_addr)
{
	struct inode *inode;

repeat:
	inode = iget5_locked(sb, no_addr, iget_test, iget_set, &no_addr);
	if (!inode)
		return inode;
	if (is_bad_inode(inode)) {
		iput(inode);
		goto repeat;
	}
	return inode;
}