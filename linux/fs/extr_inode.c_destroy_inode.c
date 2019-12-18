#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct super_operations {scalar_t__ free_inode; int /*<<< orphan*/  (* destroy_inode ) (struct inode*) ;} ;
struct inode {int /*<<< orphan*/  i_rcu; scalar_t__ free_inode; int /*<<< orphan*/  i_lru; TYPE_1__* i_sb; } ;
struct TYPE_2__ {struct super_operations* s_op; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  __destroy_inode (struct inode*) ; 
 int /*<<< orphan*/  call_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i_callback ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct inode*) ; 

__attribute__((used)) static void destroy_inode(struct inode *inode)
{
	const struct super_operations *ops = inode->i_sb->s_op;

	BUG_ON(!list_empty(&inode->i_lru));
	__destroy_inode(inode);
	if (ops->destroy_inode) {
		ops->destroy_inode(inode);
		if (!ops->free_inode)
			return;
	}
	inode->free_inode = ops->free_inode;
	call_rcu(&inode->i_rcu, i_callback);
}