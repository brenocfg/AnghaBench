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
struct net {int dummy; } ;
struct clusterip_net {int /*<<< orphan*/  mutex; int /*<<< orphan*/ * procdir; } ;

/* Variables and functions */
 int /*<<< orphan*/  cip_arp_ops ; 
 struct clusterip_net* clusterip_pernet (struct net*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nf_unregister_net_hook (struct net*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  proc_remove (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void clusterip_net_exit(struct net *net)
{
#ifdef CONFIG_PROC_FS
	struct clusterip_net *cn = clusterip_pernet(net);

	mutex_lock(&cn->mutex);
	proc_remove(cn->procdir);
	cn->procdir = NULL;
	mutex_unlock(&cn->mutex);
#endif
	nf_unregister_net_hook(net, &cip_arp_ops);
}