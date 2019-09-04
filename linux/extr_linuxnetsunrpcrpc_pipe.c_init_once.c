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
struct rpc_inode {int /*<<< orphan*/  waitq; int /*<<< orphan*/ * pipe; int /*<<< orphan*/ * private; int /*<<< orphan*/  vfs_inode; } ;

/* Variables and functions */
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  inode_init_once (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
init_once(void *foo)
{
	struct rpc_inode *rpci = (struct rpc_inode *) foo;

	inode_init_once(&rpci->vfs_inode);
	rpci->private = NULL;
	rpci->pipe = NULL;
	init_waitqueue_head(&rpci->waitq);
}