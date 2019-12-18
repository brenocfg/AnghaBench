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
typedef  int u32 ;
struct station_info {int filled; int expected_throughput; } ;
struct net_device {int dummy; } ;
struct TYPE_5__ {scalar_t__ autoneg; scalar_t__ duplex; int speed; } ;
struct ethtool_link_ksettings {TYPE_1__ base; } ;
struct batadv_hardif_neigh_node {int /*<<< orphan*/  addr; struct batadv_hard_iface* if_incoming; } ;
struct TYPE_6__ {int flags; int /*<<< orphan*/  throughput_override; } ;
struct batadv_hard_iface {TYPE_2__ bat_v; TYPE_3__* net_dev; int /*<<< orphan*/  soft_iface; } ;
typedef  int /*<<< orphan*/  link_settings ;
struct TYPE_7__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 scalar_t__ AUTONEG_ENABLE ; 
 int BATADV_FULL_DUPLEX ; 
 int BATADV_THROUGHPUT_DEFAULT_VALUE ; 
 int BATADV_WARNING_DEFAULT ; 
 int BIT (int /*<<< orphan*/ ) ; 
 scalar_t__ DUPLEX_FULL ; 
 int ENOENT ; 
 int /*<<< orphan*/  NL80211_STA_INFO_EXPECTED_THROUGHPUT ; 
 int SPEED_UNKNOWN ; 
 int __ethtool_get_link_ksettings (TYPE_3__*,struct ethtool_link_ksettings*) ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 struct net_device* batadv_get_real_netdev (TYPE_3__*) ; 
 int /*<<< orphan*/  batadv_info (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  batadv_is_cfg80211_hardif (struct batadv_hard_iface*) ; 
 scalar_t__ batadv_is_wifi_hardif (struct batadv_hard_iface*) ; 
 int cfg80211_get_station (struct net_device*,int /*<<< orphan*/ ,struct station_info*) ; 
 int /*<<< orphan*/  cfg80211_sinfo_release_content (struct station_info*) ; 
 int /*<<< orphan*/  dev_put (struct net_device*) ; 
 int /*<<< orphan*/  memset (struct ethtool_link_ksettings*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  rtnl_lock () ; 
 int /*<<< orphan*/  rtnl_unlock () ; 

__attribute__((used)) static u32 batadv_v_elp_get_throughput(struct batadv_hardif_neigh_node *neigh)
{
	struct batadv_hard_iface *hard_iface = neigh->if_incoming;
	struct ethtool_link_ksettings link_settings;
	struct net_device *real_netdev;
	struct station_info sinfo;
	u32 throughput;
	int ret;

	/* if the user specified a customised value for this interface, then
	 * return it directly
	 */
	throughput =  atomic_read(&hard_iface->bat_v.throughput_override);
	if (throughput != 0)
		return throughput;

	/* if this is a wireless device, then ask its throughput through
	 * cfg80211 API
	 */
	if (batadv_is_wifi_hardif(hard_iface)) {
		if (!batadv_is_cfg80211_hardif(hard_iface))
			/* unsupported WiFi driver version */
			goto default_throughput;

		real_netdev = batadv_get_real_netdev(hard_iface->net_dev);
		if (!real_netdev)
			goto default_throughput;

		ret = cfg80211_get_station(real_netdev, neigh->addr, &sinfo);

		if (!ret) {
			/* free the TID stats immediately */
			cfg80211_sinfo_release_content(&sinfo);
		}

		dev_put(real_netdev);
		if (ret == -ENOENT) {
			/* Node is not associated anymore! It would be
			 * possible to delete this neighbor. For now set
			 * the throughput metric to 0.
			 */
			return 0;
		}
		if (ret)
			goto default_throughput;
		if (!(sinfo.filled & BIT(NL80211_STA_INFO_EXPECTED_THROUGHPUT)))
			goto default_throughput;

		return sinfo.expected_throughput / 100;
	}

	/* if not a wifi interface, check if this device provides data via
	 * ethtool (e.g. an Ethernet adapter)
	 */
	memset(&link_settings, 0, sizeof(link_settings));
	rtnl_lock();
	ret = __ethtool_get_link_ksettings(hard_iface->net_dev, &link_settings);
	rtnl_unlock();

	/* Virtual interface drivers such as tun / tap interfaces, VLAN, etc
	 * tend to initialize the interface throughput with some value for the
	 * sake of having a throughput number to export via ethtool. This
	 * exported throughput leaves batman-adv to conclude the interface
	 * throughput is genuine (reflecting reality), thus no measurements
	 * are necessary.
	 *
	 * Based on the observation that those interface types also tend to set
	 * the link auto-negotiation to 'off', batman-adv shall check this
	 * setting to differentiate between genuine link throughput information
	 * and placeholders installed by virtual interfaces.
	 */
	if (ret == 0 && link_settings.base.autoneg == AUTONEG_ENABLE) {
		/* link characteristics might change over time */
		if (link_settings.base.duplex == DUPLEX_FULL)
			hard_iface->bat_v.flags |= BATADV_FULL_DUPLEX;
		else
			hard_iface->bat_v.flags &= ~BATADV_FULL_DUPLEX;

		throughput = link_settings.base.speed;
		if (throughput && throughput != SPEED_UNKNOWN)
			return throughput * 10;
	}

default_throughput:
	if (!(hard_iface->bat_v.flags & BATADV_WARNING_DEFAULT)) {
		batadv_info(hard_iface->soft_iface,
			    "WiFi driver or ethtool info does not provide information about link speeds on interface %s, therefore defaulting to hardcoded throughput values of %u.%1u Mbps. Consider overriding the throughput manually or checking your driver.\n",
			    hard_iface->net_dev->name,
			    BATADV_THROUGHPUT_DEFAULT_VALUE / 10,
			    BATADV_THROUGHPUT_DEFAULT_VALUE % 10);
		hard_iface->bat_v.flags |= BATADV_WARNING_DEFAULT;
	}

	/* if none of the above cases apply, return the base_throughput */
	return BATADV_THROUGHPUT_DEFAULT_VALUE;
}