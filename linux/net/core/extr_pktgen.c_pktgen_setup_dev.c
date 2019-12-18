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
struct pktgen_net {int dummy; } ;
struct pktgen_dev {struct net_device* odev; } ;
struct net_device {scalar_t__ type; } ;

/* Variables and functions */
 scalar_t__ ARPHRD_ETHER ; 
 int EINVAL ; 
 int ENETDOWN ; 
 int ENODEV ; 
 int /*<<< orphan*/  dev_put (struct net_device*) ; 
 int /*<<< orphan*/  netif_running (struct net_device*) ; 
 struct net_device* pktgen_dev_get_by_name (struct pktgen_net const*,struct pktgen_dev*,char const*) ; 
 int /*<<< orphan*/  pr_err (char*,char const*) ; 

__attribute__((used)) static int pktgen_setup_dev(const struct pktgen_net *pn,
			    struct pktgen_dev *pkt_dev, const char *ifname)
{
	struct net_device *odev;
	int err;

	/* Clean old setups */
	if (pkt_dev->odev) {
		dev_put(pkt_dev->odev);
		pkt_dev->odev = NULL;
	}

	odev = pktgen_dev_get_by_name(pn, pkt_dev, ifname);
	if (!odev) {
		pr_err("no such netdevice: \"%s\"\n", ifname);
		return -ENODEV;
	}

	if (odev->type != ARPHRD_ETHER) {
		pr_err("not an ethernet device: \"%s\"\n", ifname);
		err = -EINVAL;
	} else if (!netif_running(odev)) {
		pr_err("device is down: \"%s\"\n", ifname);
		err = -ENETDOWN;
	} else {
		pkt_dev->odev = odev;
		return 0;
	}

	dev_put(odev);
	return err;
}