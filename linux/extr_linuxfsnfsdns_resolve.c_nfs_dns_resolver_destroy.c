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

/* Variables and functions */
 int /*<<< orphan*/  nfs4_dns_resolver_ops ; 
 int /*<<< orphan*/  nfs_dns_resolver_block ; 
 int /*<<< orphan*/  rpc_pipefs_notifier_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  unregister_pernet_subsys (int /*<<< orphan*/ *) ; 

void nfs_dns_resolver_destroy(void)
{
	rpc_pipefs_notifier_unregister(&nfs_dns_resolver_block);
	unregister_pernet_subsys(&nfs4_dns_resolver_ops);
}