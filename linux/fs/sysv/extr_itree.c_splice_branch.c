#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct inode {int /*<<< orphan*/  i_sb; int /*<<< orphan*/  i_ctime; } ;
struct TYPE_6__ {scalar_t__ key; scalar_t__ bh; scalar_t__* p; } ;
typedef  TYPE_1__ Indirect ;

/* Variables and functions */
 int EAGAIN ; 
 scalar_t__ IS_SYNC (struct inode*) ; 
 int /*<<< orphan*/  bforget (scalar_t__) ; 
 int /*<<< orphan*/  current_time (struct inode*) ; 
 int /*<<< orphan*/  dirty_indirect (scalar_t__,struct inode*) ; 
 int /*<<< orphan*/  mark_inode_dirty (struct inode*) ; 
 int /*<<< orphan*/  pointers_lock ; 
 int /*<<< orphan*/  sysv_free_block (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  sysv_sync_inode (struct inode*) ; 
 int /*<<< orphan*/  verify_chain (TYPE_1__*,TYPE_1__*) ; 
 int /*<<< orphan*/  write_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  write_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static inline int splice_branch(struct inode *inode,
				Indirect chain[],
				Indirect *where,
				int num)
{
	int i;

	/* Verify that place we are splicing to is still there and vacant */
	write_lock(&pointers_lock);
	if (!verify_chain(chain, where-1) || *where->p)
		goto changed;
	*where->p = where->key;
	write_unlock(&pointers_lock);

	inode->i_ctime = current_time(inode);

	/* had we spliced it onto indirect block? */
	if (where->bh)
		dirty_indirect(where->bh, inode);

	if (IS_SYNC(inode))
		sysv_sync_inode(inode);
	else
		mark_inode_dirty(inode);
	return 0;

changed:
	write_unlock(&pointers_lock);
	for (i = 1; i < num; i++)
		bforget(where[i].bh);
	for (i = 0; i < num; i++)
		sysv_free_block(inode->i_sb, where[i].key);
	return -EAGAIN;
}