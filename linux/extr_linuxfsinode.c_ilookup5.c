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
struct inode {int dummy; } ;

/* Variables and functions */
 struct inode* ilookup5_nowait (struct super_block*,unsigned long,int (*) (struct inode*,void*),void*) ; 
 int /*<<< orphan*/  inode_unhashed (struct inode*) ; 
 int /*<<< orphan*/  iput (struct inode*) ; 
 scalar_t__ unlikely (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wait_on_inode (struct inode*) ; 

struct inode *ilookup5(struct super_block *sb, unsigned long hashval,
		int (*test)(struct inode *, void *), void *data)
{
	struct inode *inode;
again:
	inode = ilookup5_nowait(sb, hashval, test, data);
	if (inode) {
		wait_on_inode(inode);
		if (unlikely(inode_unhashed(inode))) {
			iput(inode);
			goto again;
		}
	}
	return inode;
}