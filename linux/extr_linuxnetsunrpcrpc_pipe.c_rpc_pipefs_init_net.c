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
struct sunrpc_net {int pipe_version; int /*<<< orphan*/  pipefs_sb_lock; int /*<<< orphan*/  gssd_dummy; } ;
struct net {int dummy; } ;

/* Variables and functions */
 scalar_t__ IS_ERR (int /*<<< orphan*/ ) ; 
 int PTR_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  gssd_dummy_pipe_ops ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 struct sunrpc_net* net_generic (struct net*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rpc_mkpipe_data (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sunrpc_net_id ; 

int rpc_pipefs_init_net(struct net *net)
{
	struct sunrpc_net *sn = net_generic(net, sunrpc_net_id);

	sn->gssd_dummy = rpc_mkpipe_data(&gssd_dummy_pipe_ops, 0);
	if (IS_ERR(sn->gssd_dummy))
		return PTR_ERR(sn->gssd_dummy);

	mutex_init(&sn->pipefs_sb_lock);
	sn->pipe_version = -1;
	return 0;
}