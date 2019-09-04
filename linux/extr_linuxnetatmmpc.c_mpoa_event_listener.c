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
struct notifier_block {int dummy; } ;
struct net_device {int /*<<< orphan*/  name; } ;
struct mpoa_client {int /*<<< orphan*/ * mpoad_vcc; struct net_device* dev; int /*<<< orphan*/  dev_num; } ;
struct lec_priv {int lane_version; int /*<<< orphan*/  itfnum; TYPE_1__* lane2_ops; } ;
struct TYPE_2__ {int /*<<< orphan*/  associate_indicator; } ;

/* Variables and functions */
#define  NETDEV_CHANGE 136 
#define  NETDEV_CHANGEADDR 135 
#define  NETDEV_CHANGEMTU 134 
#define  NETDEV_DOWN 133 
#define  NETDEV_GOING_DOWN 132 
#define  NETDEV_REBOOT 131 
#define  NETDEV_REGISTER 130 
#define  NETDEV_UNREGISTER 129 
#define  NETDEV_UP 128 
 int NOTIFY_DONE ; 
 struct mpoa_client* alloc_mpc () ; 
 int /*<<< orphan*/  dev_hold (struct net_device*) ; 
 int /*<<< orphan*/  dev_net (struct net_device*) ; 
 int /*<<< orphan*/  dev_put (struct net_device*) ; 
 int /*<<< orphan*/  dprintk (char*,int /*<<< orphan*/ ) ; 
 struct mpoa_client* find_mpc_by_itfnum (int /*<<< orphan*/ ) ; 
 struct mpoa_client* find_mpc_by_lec (struct net_device*) ; 
 int /*<<< orphan*/  init_net ; 
 int /*<<< orphan*/  lane2_assoc_ind ; 
 int /*<<< orphan*/  net_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct net_device* netdev_notifier_info_to_dev (void*) ; 
 struct lec_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  pr_info (char*) ; 
 int /*<<< orphan*/  start_mpc (struct mpoa_client*,struct net_device*) ; 
 int /*<<< orphan*/  stop_mpc (struct mpoa_client*) ; 
 scalar_t__ strncmp (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int mpoa_event_listener(struct notifier_block *mpoa_notifier,
			       unsigned long event, void *ptr)
{
	struct net_device *dev = netdev_notifier_info_to_dev(ptr);
	struct mpoa_client *mpc;
	struct lec_priv *priv;

	if (!net_eq(dev_net(dev), &init_net))
		return NOTIFY_DONE;

	if (strncmp(dev->name, "lec", 3))
		return NOTIFY_DONE; /* we are only interested in lec:s */

	switch (event) {
	case NETDEV_REGISTER:       /* a new lec device was allocated */
		priv = netdev_priv(dev);
		if (priv->lane_version < 2)
			break;
		priv->lane2_ops->associate_indicator = lane2_assoc_ind;
		mpc = find_mpc_by_itfnum(priv->itfnum);
		if (mpc == NULL) {
			dprintk("allocating new mpc for %s\n", dev->name);
			mpc = alloc_mpc();
			if (mpc == NULL) {
				pr_info("no new mpc");
				break;
			}
		}
		mpc->dev_num = priv->itfnum;
		mpc->dev = dev;
		dev_hold(dev);
		dprintk("(%s) was initialized\n", dev->name);
		break;
	case NETDEV_UNREGISTER:
		/* the lec device was deallocated */
		mpc = find_mpc_by_lec(dev);
		if (mpc == NULL)
			break;
		dprintk("device (%s) was deallocated\n", dev->name);
		stop_mpc(mpc);
		dev_put(mpc->dev);
		mpc->dev = NULL;
		break;
	case NETDEV_UP:
		/* the dev was ifconfig'ed up */
		mpc = find_mpc_by_lec(dev);
		if (mpc == NULL)
			break;
		if (mpc->mpoad_vcc != NULL)
			start_mpc(mpc, dev);
		break;
	case NETDEV_DOWN:
		/* the dev was ifconfig'ed down */
		/* this means that the flow of packets from the
		 * upper layer stops
		 */
		mpc = find_mpc_by_lec(dev);
		if (mpc == NULL)
			break;
		if (mpc->mpoad_vcc != NULL)
			stop_mpc(mpc);
		break;
	case NETDEV_REBOOT:
	case NETDEV_CHANGE:
	case NETDEV_CHANGEMTU:
	case NETDEV_CHANGEADDR:
	case NETDEV_GOING_DOWN:
		break;
	default:
		break;
	}

	return NOTIFY_DONE;
}