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
struct super_block {int dummy; } ;
struct rpc_clnt {int dummy; } ;
struct net {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __rpc_clnt_remove_pipedir (struct rpc_clnt*) ; 
 struct super_block* rpc_get_sb_net (struct net*) ; 
 struct net* rpc_net_ns (struct rpc_clnt*) ; 
 int /*<<< orphan*/  rpc_put_sb_net (struct net*) ; 

__attribute__((used)) static void rpc_clnt_remove_pipedir(struct rpc_clnt *clnt)
{
	struct net *net = rpc_net_ns(clnt);
	struct super_block *pipefs_sb;

	pipefs_sb = rpc_get_sb_net(net);
	if (pipefs_sb) {
		__rpc_clnt_remove_pipedir(clnt);
		rpc_put_sb_net(net);
	}
}