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
struct net_device {int /*<<< orphan*/ * netdev_ops; int /*<<< orphan*/  name; int /*<<< orphan*/  dev_addr; } ;
struct brcmf_if {size_t bsscfgidx; TYPE_1__* drvr; int /*<<< orphan*/  mac_addr; struct net_device* ndev; } ;
struct TYPE_2__ {int /*<<< orphan*/ ** iflist; } ;

/* Variables and functions */
 int EBADE ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  INFO ; 
 int /*<<< orphan*/  TRACE ; 
 int /*<<< orphan*/  brcmf_dbg (int /*<<< orphan*/ ,char*,size_t,...) ; 
 int /*<<< orphan*/  brcmf_err (char*) ; 
 int /*<<< orphan*/  brcmf_netdev_ops_p2p ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ register_netdev (struct net_device*) ; 

__attribute__((used)) static int brcmf_net_p2p_attach(struct brcmf_if *ifp)
{
	struct net_device *ndev;

	brcmf_dbg(TRACE, "Enter, bsscfgidx=%d mac=%pM\n", ifp->bsscfgidx,
		  ifp->mac_addr);
	ndev = ifp->ndev;

	ndev->netdev_ops = &brcmf_netdev_ops_p2p;

	/* set the mac address */
	memcpy(ndev->dev_addr, ifp->mac_addr, ETH_ALEN);

	if (register_netdev(ndev) != 0) {
		brcmf_err("couldn't register the p2p net device\n");
		goto fail;
	}

	brcmf_dbg(INFO, "%s: Broadcom Dongle Host Driver\n", ndev->name);

	return 0;

fail:
	ifp->drvr->iflist[ifp->bsscfgidx] = NULL;
	ndev->netdev_ops = NULL;
	return -EBADE;
}