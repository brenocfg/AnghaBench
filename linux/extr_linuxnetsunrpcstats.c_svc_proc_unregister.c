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
struct sunrpc_net {int /*<<< orphan*/  proc_net_rpc; } ;
struct net {int dummy; } ;

/* Variables and functions */
 struct sunrpc_net* net_generic (struct net*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  remove_proc_entry (char const*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  sunrpc_net_id ; 

void
svc_proc_unregister(struct net *net, const char *name)
{
	struct sunrpc_net *sn;

	sn = net_generic(net, sunrpc_net_id);
	remove_proc_entry(name, sn->proc_net_rpc);
}