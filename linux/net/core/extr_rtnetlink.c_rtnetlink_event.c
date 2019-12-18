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
struct notifier_block {int dummy; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
#define  NETDEV_BONDING_FAILOVER 140 
#define  NETDEV_CHANGEADDR 139 
#define  NETDEV_CHANGEINFODATA 138 
#define  NETDEV_CHANGELOWERSTATE 137 
#define  NETDEV_CHANGEMTU 136 
#define  NETDEV_CHANGENAME 135 
#define  NETDEV_CHANGEUPPER 134 
#define  NETDEV_CHANGE_TX_QUEUE_LEN 133 
#define  NETDEV_FEAT_CHANGE 132 
#define  NETDEV_NOTIFY_PEERS 131 
#define  NETDEV_POST_TYPE_CHANGE 130 
#define  NETDEV_REBOOT 129 
#define  NETDEV_RESEND_IGMP 128 
 int NOTIFY_DONE ; 
 int /*<<< orphan*/  RTM_NEWLINK ; 
 struct net_device* netdev_notifier_info_to_dev (void*) ; 
 int /*<<< orphan*/  rtmsg_ifinfo_event (int /*<<< orphan*/ ,struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtnl_get_event (unsigned long) ; 

__attribute__((used)) static int rtnetlink_event(struct notifier_block *this, unsigned long event, void *ptr)
{
	struct net_device *dev = netdev_notifier_info_to_dev(ptr);

	switch (event) {
	case NETDEV_REBOOT:
	case NETDEV_CHANGEMTU:
	case NETDEV_CHANGEADDR:
	case NETDEV_CHANGENAME:
	case NETDEV_FEAT_CHANGE:
	case NETDEV_BONDING_FAILOVER:
	case NETDEV_POST_TYPE_CHANGE:
	case NETDEV_NOTIFY_PEERS:
	case NETDEV_CHANGEUPPER:
	case NETDEV_RESEND_IGMP:
	case NETDEV_CHANGEINFODATA:
	case NETDEV_CHANGELOWERSTATE:
	case NETDEV_CHANGE_TX_QUEUE_LEN:
		rtmsg_ifinfo_event(RTM_NEWLINK, dev, 0, rtnl_get_event(event),
				   GFP_KERNEL, NULL, 0);
		break;
	default:
		break;
	}
	return NOTIFY_DONE;
}