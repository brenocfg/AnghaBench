#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct inode {int /*<<< orphan*/  i_rcu; TYPE_2__* i_sb; int /*<<< orphan*/  i_lru; } ;
struct TYPE_4__ {TYPE_1__* s_op; } ;
struct TYPE_3__ {int /*<<< orphan*/  (* destroy_inode ) (struct inode*) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  __destroy_inode (struct inode*) ; 
 int /*<<< orphan*/  call_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  i_callback ; 
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct inode*) ; 

__attribute__((used)) static void destroy_inode(struct inode *inode)
{
	BUG_ON(!list_empty(&inode->i_lru));
	__destroy_inode(inode);
	if (inode->i_sb->s_op->destroy_inode)
		inode->i_sb->s_op->destroy_inode(inode);
	else
		call_rcu(&inode->i_rcu, i_callback);
}