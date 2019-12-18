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
struct nfs_netns_client {int /*<<< orphan*/  kobject; } ;
struct nfs_net {struct nfs_netns_client* nfs_client; } ;

/* Variables and functions */
 int /*<<< orphan*/  KOBJ_REMOVE ; 
 int /*<<< orphan*/  kobject_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kobject_put (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kobject_uevent (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

void nfs_netns_sysfs_destroy(struct nfs_net *netns)
{
	struct nfs_netns_client *clp = netns->nfs_client;

	if (clp) {
		kobject_uevent(&clp->kobject, KOBJ_REMOVE);
		kobject_del(&clp->kobject);
		kobject_put(&clp->kobject);
		netns->nfs_client = NULL;
	}
}