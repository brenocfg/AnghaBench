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
struct inode {int /*<<< orphan*/  i_state; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  I_CREATING ; 
 struct inode* inode_insert5 (struct inode*,unsigned long,int (*) (struct inode*,void*),int /*<<< orphan*/ *,void*) ; 
 int /*<<< orphan*/  iput (struct inode*) ; 

int insert_inode_locked4(struct inode *inode, unsigned long hashval,
		int (*test)(struct inode *, void *), void *data)
{
	struct inode *old;

	inode->i_state |= I_CREATING;
	old = inode_insert5(inode, hashval, test, NULL, data);

	if (old != inode) {
		iput(old);
		return -EBUSY;
	}
	return 0;
}