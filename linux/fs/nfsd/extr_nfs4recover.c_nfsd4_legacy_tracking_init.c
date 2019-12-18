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

/* Variables and functions */
 int EINVAL ; 
 struct net init_net ; 
 int nfs4_legacy_state_init (struct net*) ; 
 int /*<<< orphan*/  nfs4_legacy_state_shutdown (struct net*) ; 
 int nfsd4_load_reboot_recovery_data (struct net*) ; 
 int /*<<< orphan*/  pr_warn (char*) ; 
 int /*<<< orphan*/  printk (char*) ; 

__attribute__((used)) static int
nfsd4_legacy_tracking_init(struct net *net)
{
	int status;

	/* XXX: The legacy code won't work in a container */
	if (net != &init_net) {
		pr_warn("NFSD: attempt to initialize legacy client tracking in a container ignored.\n");
		return -EINVAL;
	}

	status = nfs4_legacy_state_init(net);
	if (status)
		return status;

	status = nfsd4_load_reboot_recovery_data(net);
	if (status)
		goto err;
	printk("NFSD: Using legacy client tracking operations.\n");
	return 0;

err:
	nfs4_legacy_state_shutdown(net);
	return status;
}