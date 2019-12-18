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
struct packet_mclist {int type; int /*<<< orphan*/  addr; int /*<<< orphan*/  alen; } ;
struct net_device {int /*<<< orphan*/  addr_len; } ;

/* Variables and functions */
 int EINVAL ; 
#define  PACKET_MR_ALLMULTI 131 
#define  PACKET_MR_MULTICAST 130 
#define  PACKET_MR_PROMISC 129 
#define  PACKET_MR_UNICAST 128 
 int dev_mc_add (struct net_device*,int /*<<< orphan*/ ) ; 
 int dev_mc_del (struct net_device*,int /*<<< orphan*/ ) ; 
 int dev_set_allmulti (struct net_device*,int) ; 
 int dev_set_promiscuity (struct net_device*,int) ; 
 int dev_uc_add (struct net_device*,int /*<<< orphan*/ ) ; 
 int dev_uc_del (struct net_device*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int packet_dev_mc(struct net_device *dev, struct packet_mclist *i,
			 int what)
{
	switch (i->type) {
	case PACKET_MR_MULTICAST:
		if (i->alen != dev->addr_len)
			return -EINVAL;
		if (what > 0)
			return dev_mc_add(dev, i->addr);
		else
			return dev_mc_del(dev, i->addr);
		break;
	case PACKET_MR_PROMISC:
		return dev_set_promiscuity(dev, what);
	case PACKET_MR_ALLMULTI:
		return dev_set_allmulti(dev, what);
	case PACKET_MR_UNICAST:
		if (i->alen != dev->addr_len)
			return -EINVAL;
		if (what > 0)
			return dev_uc_add(dev, i->addr);
		else
			return dev_uc_del(dev, i->addr);
		break;
	default:
		break;
	}
	return 0;
}