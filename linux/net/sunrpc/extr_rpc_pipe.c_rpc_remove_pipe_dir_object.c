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
struct sunrpc_net {int /*<<< orphan*/  pipefs_sb_lock; } ;
struct rpc_pipe_dir_object {int /*<<< orphan*/  pdo_head; } ;
struct rpc_pipe_dir_head {int dummy; } ;
struct net {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_empty (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct sunrpc_net* net_generic (struct net*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rpc_remove_pipe_dir_object_locked (struct net*,struct rpc_pipe_dir_head*,struct rpc_pipe_dir_object*) ; 
 int /*<<< orphan*/  sunrpc_net_id ; 

void
rpc_remove_pipe_dir_object(struct net *net,
		struct rpc_pipe_dir_head *pdh,
		struct rpc_pipe_dir_object *pdo)
{
	if (!list_empty(&pdo->pdo_head)) {
		struct sunrpc_net *sn = net_generic(net, sunrpc_net_id);

		mutex_lock(&sn->pipefs_sb_lock);
		rpc_remove_pipe_dir_object_locked(net, pdh, pdo);
		mutex_unlock(&sn->pipefs_sb_lock);
	}
}