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
struct proc_dir_entry {int dummy; } ;
struct net {int dummy; } ;
struct file_operations {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dprintk (char*,char const*) ; 
 struct sunrpc_net* net_generic (struct net*,int /*<<< orphan*/ ) ; 
 struct proc_dir_entry* proc_create_data (char const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct file_operations const*,void*) ; 
 int /*<<< orphan*/  sunrpc_net_id ; 

__attribute__((used)) static inline struct proc_dir_entry *
do_register(struct net *net, const char *name, void *data,
	    const struct file_operations *fops)
{
	struct sunrpc_net *sn;

	dprintk("RPC:       registering /proc/net/rpc/%s\n", name);
	sn = net_generic(net, sunrpc_net_id);
	return proc_create_data(name, 0, sn->proc_net_rpc, fops, data);
}