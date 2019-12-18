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
typedef  int /*<<< orphan*/  u32 ;
struct net_device {int dummy; } ;
struct net {int dummy; } ;
struct ncsi_dev_priv {int dummy; } ;
struct ncsi_dev {int dummy; } ;

/* Variables and functions */
 struct ncsi_dev_priv* TO_NCSI_DEV_PRIV (struct ncsi_dev*) ; 
 struct net_device* dev_get_by_index (struct net*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_put (struct net_device*) ; 
 struct ncsi_dev* ncsi_find_dev (struct net_device*) ; 
 int /*<<< orphan*/  pr_err (char*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static struct ncsi_dev_priv *ndp_from_ifindex(struct net *net, u32 ifindex)
{
	struct ncsi_dev_priv *ndp;
	struct net_device *dev;
	struct ncsi_dev *nd;
	struct ncsi_dev;

	if (!net)
		return NULL;

	dev = dev_get_by_index(net, ifindex);
	if (!dev) {
		pr_err("NCSI netlink: No device for ifindex %u\n", ifindex);
		return NULL;
	}

	nd = ncsi_find_dev(dev);
	ndp = nd ? TO_NCSI_DEV_PRIV(nd) : NULL;

	dev_put(dev);
	return ndp;
}