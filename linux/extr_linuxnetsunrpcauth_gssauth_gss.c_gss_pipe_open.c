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
struct sunrpc_net {int pipe_version; int /*<<< orphan*/  pipe_users; } ;
struct net {int dummy; } ;
struct inode {TYPE_1__* i_sb; } ;
struct TYPE_2__ {struct net* s_fs_info; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 struct sunrpc_net* net_generic (struct net*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pipe_version_lock ; 
 int /*<<< orphan*/  pipe_version_rpc_waitqueue ; 
 int /*<<< orphan*/  pipe_version_waitqueue ; 
 int /*<<< orphan*/  rpc_wake_up (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  sunrpc_net_id ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int gss_pipe_open(struct inode *inode, int new_version)
{
	struct net *net = inode->i_sb->s_fs_info;
	struct sunrpc_net *sn = net_generic(net, sunrpc_net_id);
	int ret = 0;

	spin_lock(&pipe_version_lock);
	if (sn->pipe_version < 0) {
		/* First open of any gss pipe determines the version: */
		sn->pipe_version = new_version;
		rpc_wake_up(&pipe_version_rpc_waitqueue);
		wake_up(&pipe_version_waitqueue);
	} else if (sn->pipe_version != new_version) {
		/* Trying to open a pipe of a different version */
		ret = -EBUSY;
		goto out;
	}
	atomic_inc(&sn->pipe_users);
out:
	spin_unlock(&pipe_version_lock);
	return ret;

}