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
struct net {int /*<<< orphan*/  proc_net; } ;
struct clusterip_net {int /*<<< orphan*/  mutex; int /*<<< orphan*/  procdir; int /*<<< orphan*/  lock; int /*<<< orphan*/  configs; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cip_arp_ops ; 
 struct clusterip_net* clusterip_pernet (struct net*) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int nf_register_net_hook (struct net*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nf_unregister_net_hook (struct net*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 int /*<<< orphan*/  proc_mkdir (char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int clusterip_net_init(struct net *net)
{
	struct clusterip_net *cn = clusterip_pernet(net);
	int ret;

	INIT_LIST_HEAD(&cn->configs);

	spin_lock_init(&cn->lock);

	ret = nf_register_net_hook(net, &cip_arp_ops);
	if (ret < 0)
		return ret;

#ifdef CONFIG_PROC_FS
	cn->procdir = proc_mkdir("ipt_CLUSTERIP", net->proc_net);
	if (!cn->procdir) {
		nf_unregister_net_hook(net, &cip_arp_ops);
		pr_err("Unable to proc dir entry\n");
		return -ENOMEM;
	}
	mutex_init(&cn->mutex);
#endif /* CONFIG_PROC_FS */

	return 0;
}