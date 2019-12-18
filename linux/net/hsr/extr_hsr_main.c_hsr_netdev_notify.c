#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct notifier_block {int dummy; } ;
struct net_device {int /*<<< orphan*/  dev_addr; } ;
struct hsr_priv {int /*<<< orphan*/  self_node_db; } ;
struct hsr_port {TYPE_1__* dev; struct hsr_priv* hsr; int /*<<< orphan*/  type; } ;
struct TYPE_3__ {int mtu; int /*<<< orphan*/  dev_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  HSR_PT_MASTER ; 
 int /*<<< orphan*/  HSR_PT_SLAVE_A ; 
 int /*<<< orphan*/  HSR_PT_SLAVE_B ; 
#define  NETDEV_CHANGE 134 
#define  NETDEV_CHANGEADDR 133 
#define  NETDEV_CHANGEMTU 132 
#define  NETDEV_DOWN 131 
#define  NETDEV_PRE_TYPE_CHANGE 130 
#define  NETDEV_UNREGISTER 129 
#define  NETDEV_UP 128 
 int NOTIFY_BAD ; 
 int NOTIFY_DONE ; 
 int /*<<< orphan*/  call_netdevice_notifiers (int const,TYPE_1__*) ; 
 int /*<<< orphan*/  ether_addr_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hsr_check_carrier_and_operstate (struct hsr_priv*) ; 
 int hsr_create_self_node (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hsr_del_port (struct hsr_port*) ; 
 int hsr_get_max_mtu (struct hsr_priv*) ; 
 struct hsr_port* hsr_port_get_hsr (struct hsr_priv*,int /*<<< orphan*/ ) ; 
 struct hsr_port* hsr_port_get_rtnl (struct net_device*) ; 
 int /*<<< orphan*/  is_hsr_master (struct net_device*) ; 
 struct net_device* netdev_notifier_info_to_dev (void*) ; 
 struct hsr_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  netdev_warn (TYPE_1__*,char*) ; 

__attribute__((used)) static int hsr_netdev_notify(struct notifier_block *nb, unsigned long event,
			     void *ptr)
{
	struct net_device *dev;
	struct hsr_port *port, *master;
	struct hsr_priv *hsr;
	int mtu_max;
	int res;

	dev = netdev_notifier_info_to_dev(ptr);
	port = hsr_port_get_rtnl(dev);
	if (!port) {
		if (!is_hsr_master(dev))
			return NOTIFY_DONE;	/* Not an HSR device */
		hsr = netdev_priv(dev);
		port = hsr_port_get_hsr(hsr, HSR_PT_MASTER);
		if (!port) {
			/* Resend of notification concerning removed device? */
			return NOTIFY_DONE;
		}
	} else {
		hsr = port->hsr;
	}

	switch (event) {
	case NETDEV_UP:		/* Administrative state DOWN */
	case NETDEV_DOWN:	/* Administrative state UP */
	case NETDEV_CHANGE:	/* Link (carrier) state changes */
		hsr_check_carrier_and_operstate(hsr);
		break;
	case NETDEV_CHANGEADDR:
		if (port->type == HSR_PT_MASTER) {
			/* This should not happen since there's no
			 * ndo_set_mac_address() for HSR devices - i.e. not
			 * supported.
			 */
			break;
		}

		master = hsr_port_get_hsr(hsr, HSR_PT_MASTER);

		if (port->type == HSR_PT_SLAVE_A) {
			ether_addr_copy(master->dev->dev_addr, dev->dev_addr);
			call_netdevice_notifiers(NETDEV_CHANGEADDR,
						 master->dev);
		}

		/* Make sure we recognize frames from ourselves in hsr_rcv() */
		port = hsr_port_get_hsr(hsr, HSR_PT_SLAVE_B);
		res = hsr_create_self_node(&hsr->self_node_db,
					   master->dev->dev_addr,
					   port ?
						port->dev->dev_addr :
						master->dev->dev_addr);
		if (res)
			netdev_warn(master->dev,
				    "Could not update HSR node address.\n");
		break;
	case NETDEV_CHANGEMTU:
		if (port->type == HSR_PT_MASTER)
			break; /* Handled in ndo_change_mtu() */
		mtu_max = hsr_get_max_mtu(port->hsr);
		master = hsr_port_get_hsr(port->hsr, HSR_PT_MASTER);
		master->dev->mtu = mtu_max;
		break;
	case NETDEV_UNREGISTER:
		hsr_del_port(port);
		break;
	case NETDEV_PRE_TYPE_CHANGE:
		/* HSR works only on Ethernet devices. Refuse slave to change
		 * its type.
		 */
		return NOTIFY_BAD;
	}

	return NOTIFY_DONE;
}