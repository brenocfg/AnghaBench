#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct vif_params {int use_4addr; } ;
struct net_device {int priv_flags; TYPE_3__* ieee80211_ptr; } ;
struct TYPE_7__ {int interface_modes; } ;
struct cfg80211_registered_device {TYPE_2__ wiphy; TYPE_1__* ops; } ;
typedef  enum nl80211_iftype { ____Placeholder_nl80211_iftype } nl80211_iftype ;
struct TYPE_8__ {int iftype; int use_4addr; scalar_t__ mesh_id_up_len; } ;
struct TYPE_6__ {int /*<<< orphan*/  change_virtual_intf; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSERT_RTNL () ; 
 int EBUSY ; 
 int EOPNOTSUPP ; 
 int IFF_BRIDGE_PORT ; 
 int IFF_DONT_BRIDGE ; 
#define  NL80211_IFTYPE_ADHOC 141 
#define  NL80211_IFTYPE_AP 140 
#define  NL80211_IFTYPE_AP_VLAN 139 
#define  NL80211_IFTYPE_MESH_POINT 138 
#define  NL80211_IFTYPE_MONITOR 137 
#define  NL80211_IFTYPE_NAN 136 
#define  NL80211_IFTYPE_OCB 135 
#define  NL80211_IFTYPE_P2P_CLIENT 134 
#define  NL80211_IFTYPE_P2P_DEVICE 133 
#define  NL80211_IFTYPE_P2P_GO 132 
#define  NL80211_IFTYPE_STATION 131 
#define  NL80211_IFTYPE_UNSPECIFIED 130 
#define  NL80211_IFTYPE_WDS 129 
#define  NUM_NL80211_IFTYPES 128 
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  WLAN_REASON_DEAUTH_LEAVING ; 
 int /*<<< orphan*/  cfg80211_disconnect (struct cfg80211_registered_device*,struct net_device*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cfg80211_leave_ibss (struct cfg80211_registered_device*,struct net_device*,int) ; 
 int /*<<< orphan*/  cfg80211_mlme_purge_registrations (TYPE_3__*) ; 
 int /*<<< orphan*/  cfg80211_process_rdev_events (struct cfg80211_registered_device*) ; 
 int /*<<< orphan*/  cfg80211_stop_ap (struct cfg80211_registered_device*,struct net_device*,int) ; 
 int /*<<< orphan*/  cfg80211_update_iface_num (struct cfg80211_registered_device*,int,int) ; 
 scalar_t__ netif_running (struct net_device*) ; 
 int rdev_change_virtual_intf (struct cfg80211_registered_device*,struct net_device*,int,struct vif_params*) ; 
 int /*<<< orphan*/  rdev_set_qos_map (struct cfg80211_registered_device*,struct net_device*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wdev_lock (TYPE_3__*) ; 
 int /*<<< orphan*/  wdev_unlock (TYPE_3__*) ; 

int cfg80211_change_iface(struct cfg80211_registered_device *rdev,
			  struct net_device *dev, enum nl80211_iftype ntype,
			  struct vif_params *params)
{
	int err;
	enum nl80211_iftype otype = dev->ieee80211_ptr->iftype;

	ASSERT_RTNL();

	/* don't support changing VLANs, you just re-create them */
	if (otype == NL80211_IFTYPE_AP_VLAN)
		return -EOPNOTSUPP;

	/* cannot change into P2P device or NAN */
	if (ntype == NL80211_IFTYPE_P2P_DEVICE ||
	    ntype == NL80211_IFTYPE_NAN)
		return -EOPNOTSUPP;

	if (!rdev->ops->change_virtual_intf ||
	    !(rdev->wiphy.interface_modes & (1 << ntype)))
		return -EOPNOTSUPP;

	/* if it's part of a bridge, reject changing type to station/ibss */
	if ((dev->priv_flags & IFF_BRIDGE_PORT) &&
	    (ntype == NL80211_IFTYPE_ADHOC ||
	     ntype == NL80211_IFTYPE_STATION ||
	     ntype == NL80211_IFTYPE_P2P_CLIENT))
		return -EBUSY;

	if (ntype != otype) {
		dev->ieee80211_ptr->use_4addr = false;
		dev->ieee80211_ptr->mesh_id_up_len = 0;
		wdev_lock(dev->ieee80211_ptr);
		rdev_set_qos_map(rdev, dev, NULL);
		wdev_unlock(dev->ieee80211_ptr);

		switch (otype) {
		case NL80211_IFTYPE_AP:
			cfg80211_stop_ap(rdev, dev, true);
			break;
		case NL80211_IFTYPE_ADHOC:
			cfg80211_leave_ibss(rdev, dev, false);
			break;
		case NL80211_IFTYPE_STATION:
		case NL80211_IFTYPE_P2P_CLIENT:
			wdev_lock(dev->ieee80211_ptr);
			cfg80211_disconnect(rdev, dev,
					    WLAN_REASON_DEAUTH_LEAVING, true);
			wdev_unlock(dev->ieee80211_ptr);
			break;
		case NL80211_IFTYPE_MESH_POINT:
			/* mesh should be handled? */
			break;
		default:
			break;
		}

		cfg80211_process_rdev_events(rdev);
		cfg80211_mlme_purge_registrations(dev->ieee80211_ptr);
	}

	err = rdev_change_virtual_intf(rdev, dev, ntype, params);

	WARN_ON(!err && dev->ieee80211_ptr->iftype != ntype);

	if (!err && params && params->use_4addr != -1)
		dev->ieee80211_ptr->use_4addr = params->use_4addr;

	if (!err) {
		dev->priv_flags &= ~IFF_DONT_BRIDGE;
		switch (ntype) {
		case NL80211_IFTYPE_STATION:
			if (dev->ieee80211_ptr->use_4addr)
				break;
			/* fall through */
		case NL80211_IFTYPE_OCB:
		case NL80211_IFTYPE_P2P_CLIENT:
		case NL80211_IFTYPE_ADHOC:
			dev->priv_flags |= IFF_DONT_BRIDGE;
			break;
		case NL80211_IFTYPE_P2P_GO:
		case NL80211_IFTYPE_AP:
		case NL80211_IFTYPE_AP_VLAN:
		case NL80211_IFTYPE_WDS:
		case NL80211_IFTYPE_MESH_POINT:
			/* bridging OK */
			break;
		case NL80211_IFTYPE_MONITOR:
			/* monitor can't bridge anyway */
			break;
		case NL80211_IFTYPE_UNSPECIFIED:
		case NUM_NL80211_IFTYPES:
			/* not happening */
			break;
		case NL80211_IFTYPE_P2P_DEVICE:
		case NL80211_IFTYPE_NAN:
			WARN_ON(1);
			break;
		}
	}

	if (!err && ntype != otype && netif_running(dev)) {
		cfg80211_update_iface_num(rdev, ntype, 1);
		cfg80211_update_iface_num(rdev, otype, -1);
	}

	return err;
}