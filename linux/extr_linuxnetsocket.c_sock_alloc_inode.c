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
struct super_block {int dummy; } ;
struct socket_wq {scalar_t__ flags; int /*<<< orphan*/ * fasync_list; int /*<<< orphan*/  wait; } ;
struct inode {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/ * file; int /*<<< orphan*/ * sk; int /*<<< orphan*/ * ops; scalar_t__ flags; int /*<<< orphan*/  state; struct socket_wq* wq; } ;
struct socket_alloc {struct inode vfs_inode; TYPE_1__ socket; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  SS_UNCONNECTED ; 
 int /*<<< orphan*/  init_waitqueue_head (int /*<<< orphan*/ *) ; 
 struct socket_wq* kmalloc (int,int /*<<< orphan*/ ) ; 
 struct socket_alloc* kmem_cache_alloc (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kmem_cache_free (int /*<<< orphan*/ ,struct socket_alloc*) ; 
 int /*<<< orphan*/  sock_inode_cachep ; 

__attribute__((used)) static struct inode *sock_alloc_inode(struct super_block *sb)
{
	struct socket_alloc *ei;
	struct socket_wq *wq;

	ei = kmem_cache_alloc(sock_inode_cachep, GFP_KERNEL);
	if (!ei)
		return NULL;
	wq = kmalloc(sizeof(*wq), GFP_KERNEL);
	if (!wq) {
		kmem_cache_free(sock_inode_cachep, ei);
		return NULL;
	}
	init_waitqueue_head(&wq->wait);
	wq->fasync_list = NULL;
	wq->flags = 0;
	ei->socket.wq = wq;

	ei->socket.state = SS_UNCONNECTED;
	ei->socket.flags = 0;
	ei->socket.ops = NULL;
	ei->socket.sk = NULL;
	ei->socket.file = NULL;

	return &ei->vfs_inode;
}