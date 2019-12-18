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
struct sunrpc_net {struct rpc_pipe* gssd_dummy; } ;
struct rpc_pipe {scalar_t__ nwriters; scalar_t__ nreaders; } ;
struct net {int dummy; } ;

/* Variables and functions */
 struct sunrpc_net* net_generic (struct net*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sunrpc_net_id ; 

bool
gssd_running(struct net *net)
{
	struct sunrpc_net *sn = net_generic(net, sunrpc_net_id);
	struct rpc_pipe *pipe = sn->gssd_dummy;

	return pipe->nreaders || pipe->nwriters;
}