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
struct nfsd_net {int /*<<< orphan*/  boot_time; } ;
struct net {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 struct net init_net ; 
 int /*<<< orphan*/  kfree (char*) ; 
 struct nfsd_net* net_generic (struct net*,int /*<<< orphan*/ ) ; 
 char* nfsd4_cltrack_grace_start (int /*<<< orphan*/ ) ; 
 int nfsd4_umh_cltrack_upcall (char*,int /*<<< orphan*/ *,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nfsd_net_id ; 
 int /*<<< orphan*/  pr_warn (char*) ; 
 int /*<<< orphan*/  printk (char*) ; 

__attribute__((used)) static int
nfsd4_umh_cltrack_init(struct net *net)
{
	int ret;
	struct nfsd_net *nn = net_generic(net, nfsd_net_id);
	char *grace_start = nfsd4_cltrack_grace_start(nn->boot_time);

	/* XXX: The usermode helper s not working in container yet. */
	if (net != &init_net) {
		pr_warn("NFSD: attempt to initialize umh client tracking in a container ignored.\n");
		kfree(grace_start);
		return -EINVAL;
	}

	ret = nfsd4_umh_cltrack_upcall("init", NULL, grace_start, NULL);
	kfree(grace_start);
	if (!ret)
		printk("NFSD: Using UMH upcall client tracking operations.\n");
	return ret;
}