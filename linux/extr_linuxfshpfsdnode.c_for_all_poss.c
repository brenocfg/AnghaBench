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
struct hpfs_inode_info {int /*<<< orphan*/ ** i_rddir_off; } ;
typedef  int /*<<< orphan*/  loff_t ;

/* Variables and functions */
 struct hpfs_inode_info* hpfs_i (struct inode*) ; 
 void stub1 (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void for_all_poss(struct inode *inode, void (*f)(loff_t *, loff_t, loff_t),
			 loff_t p1, loff_t p2)
{
	struct hpfs_inode_info *hpfs_inode = hpfs_i(inode);
	loff_t **i;

	if (!hpfs_inode->i_rddir_off) return;
	for (i = hpfs_inode->i_rddir_off; *i; i++) (*f)(*i, p1, p2);
	return;
}