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
typedef  size_t u32 ;
struct svc_serv {int dummy; } ;
struct nfs_net {scalar_t__* cb_users; } ;
struct TYPE_2__ {int /*<<< orphan*/  inum; } ;
struct net {TYPE_1__ ns; } ;

/* Variables and functions */
 int /*<<< orphan*/  dprintk (char*,int /*<<< orphan*/ ) ; 
 struct nfs_net* net_generic (struct net*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfs_net_id ; 
 int /*<<< orphan*/  svc_shutdown_net (struct svc_serv*,struct net*) ; 

__attribute__((used)) static void nfs_callback_down_net(u32 minorversion, struct svc_serv *serv, struct net *net)
{
	struct nfs_net *nn = net_generic(net, nfs_net_id);

	if (--nn->cb_users[minorversion])
		return;

	dprintk("NFS: destroy per-net callback data; net=%x\n", net->ns.inum);
	svc_shutdown_net(serv, net);
}