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
struct net_device {scalar_t__ type; } ;
struct TYPE_2__ {scalar_t__ addr_gen_mode; } ;
struct inet6_dev {TYPE_1__ cnf; } ;

/* Variables and functions */
 scalar_t__ ARPHRD_6LOWPAN ; 
 scalar_t__ ARPHRD_ARCNET ; 
 scalar_t__ ARPHRD_ETHER ; 
 scalar_t__ ARPHRD_FDDI ; 
 scalar_t__ ARPHRD_IEEE1394 ; 
 scalar_t__ ARPHRD_INFINIBAND ; 
 scalar_t__ ARPHRD_IP6GRE ; 
 scalar_t__ ARPHRD_IPGRE ; 
 scalar_t__ ARPHRD_NONE ; 
 scalar_t__ ARPHRD_RAWIP ; 
 scalar_t__ ARPHRD_TUNNEL ; 
 scalar_t__ ARPHRD_TUNNEL6 ; 
 int /*<<< orphan*/  ASSERT_RTNL () ; 
 scalar_t__ IN6_ADDR_GEN_MODE_EUI64 ; 
 scalar_t__ IN6_ADDR_GEN_MODE_RANDOM ; 
 scalar_t__ IS_ERR (struct inet6_dev*) ; 
 struct inet6_dev* addrconf_add_dev (struct net_device*) ; 
 int /*<<< orphan*/  addrconf_addr_gen (struct inet6_dev*,int) ; 

__attribute__((used)) static void addrconf_dev_config(struct net_device *dev)
{
	struct inet6_dev *idev;

	ASSERT_RTNL();

	if ((dev->type != ARPHRD_ETHER) &&
	    (dev->type != ARPHRD_FDDI) &&
	    (dev->type != ARPHRD_ARCNET) &&
	    (dev->type != ARPHRD_INFINIBAND) &&
	    (dev->type != ARPHRD_IEEE1394) &&
	    (dev->type != ARPHRD_TUNNEL6) &&
	    (dev->type != ARPHRD_6LOWPAN) &&
	    (dev->type != ARPHRD_IP6GRE) &&
	    (dev->type != ARPHRD_IPGRE) &&
	    (dev->type != ARPHRD_TUNNEL) &&
	    (dev->type != ARPHRD_NONE) &&
	    (dev->type != ARPHRD_RAWIP)) {
		/* Alas, we support only Ethernet autoconfiguration. */
		return;
	}

	idev = addrconf_add_dev(dev);
	if (IS_ERR(idev))
		return;

	/* this device type has no EUI support */
	if (dev->type == ARPHRD_NONE &&
	    idev->cnf.addr_gen_mode == IN6_ADDR_GEN_MODE_EUI64)
		idev->cnf.addr_gen_mode = IN6_ADDR_GEN_MODE_RANDOM;

	addrconf_addr_gen(idev, false);
}