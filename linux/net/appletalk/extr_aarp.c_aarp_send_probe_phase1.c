#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {scalar_t__ s_node; int /*<<< orphan*/  s_net; } ;
struct sockaddr_at {TYPE_2__ sat_addr; } ;
struct net_device_ops {int /*<<< orphan*/  (* ndo_do_ioctl ) (TYPE_3__*,struct ifreq*,int /*<<< orphan*/ ) ;} ;
struct ifreq {int /*<<< orphan*/  ifr_addr; } ;
struct TYPE_5__ {scalar_t__ s_node; scalar_t__ s_net; } ;
struct atalk_iface {TYPE_1__ address; int /*<<< orphan*/  status; TYPE_3__* dev; } ;
struct TYPE_7__ {struct net_device_ops* netdev_ops; } ;

/* Variables and functions */
 int /*<<< orphan*/  ATIF_PROBE_FAIL ; 
 int /*<<< orphan*/  SIOCGIFADDR ; 
 int /*<<< orphan*/  SIOCSIFADDR ; 
 scalar_t__ htons (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ntohs (scalar_t__) ; 
 int /*<<< orphan*/  stub1 (TYPE_3__*,struct ifreq*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub2 (TYPE_3__*,struct ifreq*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void aarp_send_probe_phase1(struct atalk_iface *iface)
{
	struct ifreq atreq;
	struct sockaddr_at *sa = (struct sockaddr_at *)&atreq.ifr_addr;
	const struct net_device_ops *ops = iface->dev->netdev_ops;

	sa->sat_addr.s_node = iface->address.s_node;
	sa->sat_addr.s_net = ntohs(iface->address.s_net);

	/* We pass the Net:Node to the drivers/cards by a Device ioctl. */
	if (!(ops->ndo_do_ioctl(iface->dev, &atreq, SIOCSIFADDR))) {
		ops->ndo_do_ioctl(iface->dev, &atreq, SIOCGIFADDR);
		if (iface->address.s_net != htons(sa->sat_addr.s_net) ||
		    iface->address.s_node != sa->sat_addr.s_node)
			iface->status |= ATIF_PROBE_FAIL;

		iface->address.s_net  = htons(sa->sat_addr.s_net);
		iface->address.s_node = sa->sat_addr.s_node;
	}
}