#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int dummy; } ;
struct TYPE_3__ {int flags; scalar_t__ max_sched_scan_reqs; } ;
struct cfg80211_registered_device {TYPE_2__* ops; TYPE_1__ wiphy; } ;
struct TYPE_4__ {scalar_t__ deauth; scalar_t__ disconnect; scalar_t__ auth; scalar_t__ connect; scalar_t__ join_mesh; scalar_t__ start_ap; scalar_t__ set_monitor_channel; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSOCIATE ; 
 int /*<<< orphan*/  AUTHENTICATE ; 
 int /*<<< orphan*/  CMD (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  DEAUTHENTICATE ; 
 int /*<<< orphan*/  DEL_PMKSA ; 
 int /*<<< orphan*/  DISASSOCIATE ; 
 int ENOBUFS ; 
 int /*<<< orphan*/  FLUSH_PMKSA ; 
 int /*<<< orphan*/  FRAME ; 
 int /*<<< orphan*/  FRAME_WAIT_CANCEL ; 
 int /*<<< orphan*/  JOIN_IBSS ; 
 int /*<<< orphan*/  JOIN_MESH ; 
 int /*<<< orphan*/  NEW_INTERFACE ; 
 int /*<<< orphan*/  NEW_KEY ; 
 int /*<<< orphan*/  NEW_MPATH ; 
 int /*<<< orphan*/  NEW_STATION ; 
 int /*<<< orphan*/  NL80211_CMD_CONNECT ; 
 int /*<<< orphan*/  NL80211_CMD_DISCONNECT ; 
 int /*<<< orphan*/  NL80211_CMD_REGISTER_BEACONS ; 
 int /*<<< orphan*/  NL80211_CMD_SET_CHANNEL ; 
 int /*<<< orphan*/  NL80211_CMD_SET_WIPHY_NETNS ; 
 int /*<<< orphan*/  PROBE_CLIENT ; 
 int /*<<< orphan*/  REMAIN_ON_CHANNEL ; 
 int /*<<< orphan*/  SET_BSS ; 
 int /*<<< orphan*/  SET_INTERFACE ; 
 int /*<<< orphan*/  SET_MCAST_RATE ; 
 int /*<<< orphan*/  SET_MESH_CONFIG ; 
 int /*<<< orphan*/  SET_NOACK_MAP ; 
 int /*<<< orphan*/  SET_PMKSA ; 
 int /*<<< orphan*/  SET_TX_BITRATE_MASK ; 
 int /*<<< orphan*/  SET_WDS_PEER ; 
 int /*<<< orphan*/  START_AP ; 
 int /*<<< orphan*/  START_P2P_DEVICE ; 
 int /*<<< orphan*/  START_SCHED_SCAN ; 
 int /*<<< orphan*/  TDLS_MGMT ; 
 int /*<<< orphan*/  TDLS_OPER ; 
 int /*<<< orphan*/  TESTMODE ; 
 int WIPHY_FLAG_HAS_REMAIN_ON_CHANNEL ; 
 int WIPHY_FLAG_NETNS_OK ; 
 int WIPHY_FLAG_REPORTS_OBSS ; 
 int WIPHY_FLAG_SUPPORTS_TDLS ; 
 int /*<<< orphan*/  add_key ; 
 int /*<<< orphan*/  add_mpath ; 
 int /*<<< orphan*/  add_station ; 
 int /*<<< orphan*/  add_virtual_intf ; 
 int /*<<< orphan*/  assoc ; 
 int /*<<< orphan*/  auth ; 
 int /*<<< orphan*/  change_bss ; 
 int /*<<< orphan*/  change_virtual_intf ; 
 int /*<<< orphan*/  deauth ; 
 int /*<<< orphan*/  del_pmksa ; 
 int /*<<< orphan*/  disassoc ; 
 int /*<<< orphan*/  flush_pmksa ; 
 int /*<<< orphan*/  join_ibss ; 
 int /*<<< orphan*/  join_mesh ; 
 int /*<<< orphan*/  mgmt_tx ; 
 int /*<<< orphan*/  mgmt_tx_cancel_wait ; 
 scalar_t__ nla_put_u32 (struct sk_buff*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  probe_client ; 
 int /*<<< orphan*/  remain_on_channel ; 
 int /*<<< orphan*/  sched_scan_start ; 
 int /*<<< orphan*/  set_bitrate_mask ; 
 int /*<<< orphan*/  set_mcast_rate ; 
 int /*<<< orphan*/  set_noack_map ; 
 int /*<<< orphan*/  set_pmksa ; 
 int /*<<< orphan*/  set_wds_peer ; 
 int /*<<< orphan*/  start_ap ; 
 int /*<<< orphan*/  start_p2p_device ; 
 int /*<<< orphan*/  tdls_mgmt ; 
 int /*<<< orphan*/  tdls_oper ; 
 int /*<<< orphan*/  testmode_cmd ; 
 int /*<<< orphan*/  update_mesh_config ; 

__attribute__((used)) static int nl80211_add_commands_unsplit(struct cfg80211_registered_device *rdev,
					struct sk_buff *msg)
{
	int i = 0;

	/*
	 * do *NOT* add anything into this function, new things need to be
	 * advertised only to new versions of userspace that can deal with
	 * the split (and they can't possibly care about new features...
	 */
	CMD(add_virtual_intf, NEW_INTERFACE);
	CMD(change_virtual_intf, SET_INTERFACE);
	CMD(add_key, NEW_KEY);
	CMD(start_ap, START_AP);
	CMD(add_station, NEW_STATION);
	CMD(add_mpath, NEW_MPATH);
	CMD(update_mesh_config, SET_MESH_CONFIG);
	CMD(change_bss, SET_BSS);
	CMD(auth, AUTHENTICATE);
	CMD(assoc, ASSOCIATE);
	CMD(deauth, DEAUTHENTICATE);
	CMD(disassoc, DISASSOCIATE);
	CMD(join_ibss, JOIN_IBSS);
	CMD(join_mesh, JOIN_MESH);
	CMD(set_pmksa, SET_PMKSA);
	CMD(del_pmksa, DEL_PMKSA);
	CMD(flush_pmksa, FLUSH_PMKSA);
	if (rdev->wiphy.flags & WIPHY_FLAG_HAS_REMAIN_ON_CHANNEL)
		CMD(remain_on_channel, REMAIN_ON_CHANNEL);
	CMD(set_bitrate_mask, SET_TX_BITRATE_MASK);
	CMD(mgmt_tx, FRAME);
	CMD(mgmt_tx_cancel_wait, FRAME_WAIT_CANCEL);
	if (rdev->wiphy.flags & WIPHY_FLAG_NETNS_OK) {
		i++;
		if (nla_put_u32(msg, i, NL80211_CMD_SET_WIPHY_NETNS))
			goto nla_put_failure;
	}
	if (rdev->ops->set_monitor_channel || rdev->ops->start_ap ||
	    rdev->ops->join_mesh) {
		i++;
		if (nla_put_u32(msg, i, NL80211_CMD_SET_CHANNEL))
			goto nla_put_failure;
	}
	CMD(set_wds_peer, SET_WDS_PEER);
	if (rdev->wiphy.flags & WIPHY_FLAG_SUPPORTS_TDLS) {
		CMD(tdls_mgmt, TDLS_MGMT);
		CMD(tdls_oper, TDLS_OPER);
	}
	if (rdev->wiphy.max_sched_scan_reqs)
		CMD(sched_scan_start, START_SCHED_SCAN);
	CMD(probe_client, PROBE_CLIENT);
	CMD(set_noack_map, SET_NOACK_MAP);
	if (rdev->wiphy.flags & WIPHY_FLAG_REPORTS_OBSS) {
		i++;
		if (nla_put_u32(msg, i, NL80211_CMD_REGISTER_BEACONS))
			goto nla_put_failure;
	}
	CMD(start_p2p_device, START_P2P_DEVICE);
	CMD(set_mcast_rate, SET_MCAST_RATE);
#ifdef CONFIG_NL80211_TESTMODE
	CMD(testmode_cmd, TESTMODE);
#endif

	if (rdev->ops->connect || rdev->ops->auth) {
		i++;
		if (nla_put_u32(msg, i, NL80211_CMD_CONNECT))
			goto nla_put_failure;
	}

	if (rdev->ops->disconnect || rdev->ops->deauth) {
		i++;
		if (nla_put_u32(msg, i, NL80211_CMD_DISCONNECT))
			goto nla_put_failure;
	}

	return i;
 nla_put_failure:
	return -ENOBUFS;
}