#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct sockaddr {int /*<<< orphan*/  sa_data; int /*<<< orphan*/  sa_family; } ;
struct net_device {int /*<<< orphan*/ * dev_addr; } ;
struct iw_request_info {int dummy; } ;
struct TYPE_5__ {int /*<<< orphan*/ * remote_addr; } ;
struct TYPE_6__ {TYPE_1__ wds; } ;
struct hostap_interface {int type; TYPE_2__ u; TYPE_4__* local; } ;
struct TYPE_8__ {int /*<<< orphan*/ * bssid; TYPE_3__* func; int /*<<< orphan*/ * assoc_ap_addr; } ;
typedef  TYPE_4__ local_info_t ;
struct TYPE_7__ {int /*<<< orphan*/  (* get_rid ) (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ;} ;

/* Variables and functions */
 int /*<<< orphan*/  ARPHRD_ETHER ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  ETH_ALEN ; 
 int /*<<< orphan*/  HFA384X_RID_CURRENTBSSID ; 
#define  HOSTAP_INTERFACE_AP 130 
#define  HOSTAP_INTERFACE_STA 129 
#define  HOSTAP_INTERFACE_WDS 128 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 struct hostap_interface* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  stub1 (struct net_device*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int prism2_ioctl_giwap(struct net_device *dev,
			      struct iw_request_info *info,
			      struct sockaddr *ap_addr, char *extra)
{
	struct hostap_interface *iface;
	local_info_t *local;

	iface = netdev_priv(dev);
	local = iface->local;

	ap_addr->sa_family = ARPHRD_ETHER;
	switch (iface->type) {
	case HOSTAP_INTERFACE_AP:
		memcpy(&ap_addr->sa_data, dev->dev_addr, ETH_ALEN);
		break;
	case HOSTAP_INTERFACE_STA:
		memcpy(&ap_addr->sa_data, local->assoc_ap_addr, ETH_ALEN);
		break;
	case HOSTAP_INTERFACE_WDS:
		memcpy(&ap_addr->sa_data, iface->u.wds.remote_addr, ETH_ALEN);
		break;
	default:
		if (local->func->get_rid(dev, HFA384X_RID_CURRENTBSSID,
					 &ap_addr->sa_data, ETH_ALEN, 1) < 0)
			return -EOPNOTSUPP;

		/* local->bssid is also updated in LinkStatus handler when in
		 * station mode */
		memcpy(local->bssid, &ap_addr->sa_data, ETH_ALEN);
		break;
	}

	return 0;
}