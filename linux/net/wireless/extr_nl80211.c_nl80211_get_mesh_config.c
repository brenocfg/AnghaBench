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
struct wireless_dev {scalar_t__ iftype; int /*<<< orphan*/  mesh_id_len; } ;
struct sk_buff {int dummy; } ;
struct nlattr {int dummy; } ;
struct net_device {int /*<<< orphan*/  ifindex; TYPE_1__* ops; struct wireless_dev* ieee80211_ptr; } ;
struct mesh_config {int /*<<< orphan*/  dot11MeshConnectedToMeshGate; int /*<<< orphan*/  plink_timeout; int /*<<< orphan*/  dot11MeshAwakeWindowDuration; int /*<<< orphan*/  power_mode; int /*<<< orphan*/  dot11MeshHWMPconfirmationInterval; int /*<<< orphan*/  dot11MeshHWMProotInterval; int /*<<< orphan*/  dot11MeshHWMPactivePathToRootTimeout; int /*<<< orphan*/  ht_opmode; int /*<<< orphan*/  rssi_threshold; int /*<<< orphan*/  dot11MeshForwarding; int /*<<< orphan*/  dot11MeshGateAnnouncementProtocol; int /*<<< orphan*/  dot11MeshHWMPRannInterval; int /*<<< orphan*/  dot11MeshHWMPRootMode; int /*<<< orphan*/  dot11MeshHWMPnetDiameterTraversalTime; int /*<<< orphan*/  dot11MeshHWMPperrMinInterval; int /*<<< orphan*/  dot11MeshHWMPpreqMinInterval; int /*<<< orphan*/  dot11MeshHWMPactivePathTimeout; int /*<<< orphan*/  min_discovery_timeout; int /*<<< orphan*/  path_refresh_time; int /*<<< orphan*/  dot11MeshHWMPmaxPREQretries; int /*<<< orphan*/  dot11MeshNbrOffsetMaxNeighbor; int /*<<< orphan*/  auto_open_plinks; int /*<<< orphan*/  element_ttl; int /*<<< orphan*/  dot11MeshTTL; int /*<<< orphan*/  dot11MeshMaxRetries; int /*<<< orphan*/  dot11MeshMaxPeerLinks; int /*<<< orphan*/  dot11MeshHoldingTimeout; int /*<<< orphan*/  dot11MeshConfirmTimeout; int /*<<< orphan*/  dot11MeshRetryTimeout; } ;
struct genl_info {int /*<<< orphan*/  snd_seq; int /*<<< orphan*/  snd_portid; struct net_device** user_ptr; } ;
struct cfg80211_registered_device {int /*<<< orphan*/  ifindex; TYPE_1__* ops; struct wireless_dev* ieee80211_ptr; } ;
typedef  int /*<<< orphan*/  cur_params ;
struct TYPE_2__ {int /*<<< orphan*/  get_mesh_config; } ;

/* Variables and functions */
 int ENOBUFS ; 
 int ENOMEM ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  NL80211_ATTR_IFINDEX ; 
 int /*<<< orphan*/  NL80211_ATTR_MESH_CONFIG ; 
 int /*<<< orphan*/  NL80211_CMD_GET_MESH_CONFIG ; 
 scalar_t__ NL80211_IFTYPE_MESH_POINT ; 
 int /*<<< orphan*/  NL80211_MESHCONF_AUTO_OPEN_PLINKS ; 
 int /*<<< orphan*/  NL80211_MESHCONF_AWAKE_WINDOW ; 
 int /*<<< orphan*/  NL80211_MESHCONF_CONFIRM_TIMEOUT ; 
 int /*<<< orphan*/  NL80211_MESHCONF_CONNECTED_TO_GATE ; 
 int /*<<< orphan*/  NL80211_MESHCONF_ELEMENT_TTL ; 
 int /*<<< orphan*/  NL80211_MESHCONF_FORWARDING ; 
 int /*<<< orphan*/  NL80211_MESHCONF_GATE_ANNOUNCEMENTS ; 
 int /*<<< orphan*/  NL80211_MESHCONF_HOLDING_TIMEOUT ; 
 int /*<<< orphan*/  NL80211_MESHCONF_HT_OPMODE ; 
 int /*<<< orphan*/  NL80211_MESHCONF_HWMP_ACTIVE_PATH_TIMEOUT ; 
 int /*<<< orphan*/  NL80211_MESHCONF_HWMP_CONFIRMATION_INTERVAL ; 
 int /*<<< orphan*/  NL80211_MESHCONF_HWMP_MAX_PREQ_RETRIES ; 
 int /*<<< orphan*/  NL80211_MESHCONF_HWMP_NET_DIAM_TRVS_TIME ; 
 int /*<<< orphan*/  NL80211_MESHCONF_HWMP_PATH_TO_ROOT_TIMEOUT ; 
 int /*<<< orphan*/  NL80211_MESHCONF_HWMP_PERR_MIN_INTERVAL ; 
 int /*<<< orphan*/  NL80211_MESHCONF_HWMP_PREQ_MIN_INTERVAL ; 
 int /*<<< orphan*/  NL80211_MESHCONF_HWMP_RANN_INTERVAL ; 
 int /*<<< orphan*/  NL80211_MESHCONF_HWMP_ROOTMODE ; 
 int /*<<< orphan*/  NL80211_MESHCONF_HWMP_ROOT_INTERVAL ; 
 int /*<<< orphan*/  NL80211_MESHCONF_MAX_PEER_LINKS ; 
 int /*<<< orphan*/  NL80211_MESHCONF_MAX_RETRIES ; 
 int /*<<< orphan*/  NL80211_MESHCONF_MIN_DISCOVERY_TIMEOUT ; 
 int /*<<< orphan*/  NL80211_MESHCONF_PATH_REFRESH_TIME ; 
 int /*<<< orphan*/  NL80211_MESHCONF_PLINK_TIMEOUT ; 
 int /*<<< orphan*/  NL80211_MESHCONF_POWER_MODE ; 
 int /*<<< orphan*/  NL80211_MESHCONF_RETRY_TIMEOUT ; 
 int /*<<< orphan*/  NL80211_MESHCONF_RSSI_THRESHOLD ; 
 int /*<<< orphan*/  NL80211_MESHCONF_SYNC_OFFSET_MAX_NEIGHBOR ; 
 int /*<<< orphan*/  NL80211_MESHCONF_TTL ; 
 int /*<<< orphan*/  NLMSG_DEFAULT_SIZE ; 
 int /*<<< orphan*/  default_mesh_config ; 
 int /*<<< orphan*/  genlmsg_end (struct sk_buff*,void*) ; 
 int genlmsg_reply (struct sk_buff*,struct genl_info*) ; 
 int /*<<< orphan*/  memcpy (struct mesh_config*,int /*<<< orphan*/ *,int) ; 
 void* nl80211hdr_put (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nla_nest_end (struct sk_buff*,struct nlattr*) ; 
 struct nlattr* nla_nest_start_noflag (struct sk_buff*,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_s32 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_u16 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_u32 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ nla_put_u8 (struct sk_buff*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nlmsg_free (struct sk_buff*) ; 
 struct sk_buff* nlmsg_new (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int rdev_get_mesh_config (struct net_device*,struct net_device*,struct mesh_config*) ; 
 int /*<<< orphan*/  wdev_lock (struct wireless_dev*) ; 
 int /*<<< orphan*/  wdev_unlock (struct wireless_dev*) ; 

__attribute__((used)) static int nl80211_get_mesh_config(struct sk_buff *skb,
				   struct genl_info *info)
{
	struct cfg80211_registered_device *rdev = info->user_ptr[0];
	struct net_device *dev = info->user_ptr[1];
	struct wireless_dev *wdev = dev->ieee80211_ptr;
	struct mesh_config cur_params;
	int err = 0;
	void *hdr;
	struct nlattr *pinfoattr;
	struct sk_buff *msg;

	if (wdev->iftype != NL80211_IFTYPE_MESH_POINT)
		return -EOPNOTSUPP;

	if (!rdev->ops->get_mesh_config)
		return -EOPNOTSUPP;

	wdev_lock(wdev);
	/* If not connected, get default parameters */
	if (!wdev->mesh_id_len)
		memcpy(&cur_params, &default_mesh_config, sizeof(cur_params));
	else
		err = rdev_get_mesh_config(rdev, dev, &cur_params);
	wdev_unlock(wdev);

	if (err)
		return err;

	/* Draw up a netlink message to send back */
	msg = nlmsg_new(NLMSG_DEFAULT_SIZE, GFP_KERNEL);
	if (!msg)
		return -ENOMEM;
	hdr = nl80211hdr_put(msg, info->snd_portid, info->snd_seq, 0,
			     NL80211_CMD_GET_MESH_CONFIG);
	if (!hdr)
		goto out;
	pinfoattr = nla_nest_start_noflag(msg, NL80211_ATTR_MESH_CONFIG);
	if (!pinfoattr)
		goto nla_put_failure;
	if (nla_put_u32(msg, NL80211_ATTR_IFINDEX, dev->ifindex) ||
	    nla_put_u16(msg, NL80211_MESHCONF_RETRY_TIMEOUT,
			cur_params.dot11MeshRetryTimeout) ||
	    nla_put_u16(msg, NL80211_MESHCONF_CONFIRM_TIMEOUT,
			cur_params.dot11MeshConfirmTimeout) ||
	    nla_put_u16(msg, NL80211_MESHCONF_HOLDING_TIMEOUT,
			cur_params.dot11MeshHoldingTimeout) ||
	    nla_put_u16(msg, NL80211_MESHCONF_MAX_PEER_LINKS,
			cur_params.dot11MeshMaxPeerLinks) ||
	    nla_put_u8(msg, NL80211_MESHCONF_MAX_RETRIES,
		       cur_params.dot11MeshMaxRetries) ||
	    nla_put_u8(msg, NL80211_MESHCONF_TTL,
		       cur_params.dot11MeshTTL) ||
	    nla_put_u8(msg, NL80211_MESHCONF_ELEMENT_TTL,
		       cur_params.element_ttl) ||
	    nla_put_u8(msg, NL80211_MESHCONF_AUTO_OPEN_PLINKS,
		       cur_params.auto_open_plinks) ||
	    nla_put_u32(msg, NL80211_MESHCONF_SYNC_OFFSET_MAX_NEIGHBOR,
			cur_params.dot11MeshNbrOffsetMaxNeighbor) ||
	    nla_put_u8(msg, NL80211_MESHCONF_HWMP_MAX_PREQ_RETRIES,
		       cur_params.dot11MeshHWMPmaxPREQretries) ||
	    nla_put_u32(msg, NL80211_MESHCONF_PATH_REFRESH_TIME,
			cur_params.path_refresh_time) ||
	    nla_put_u16(msg, NL80211_MESHCONF_MIN_DISCOVERY_TIMEOUT,
			cur_params.min_discovery_timeout) ||
	    nla_put_u32(msg, NL80211_MESHCONF_HWMP_ACTIVE_PATH_TIMEOUT,
			cur_params.dot11MeshHWMPactivePathTimeout) ||
	    nla_put_u16(msg, NL80211_MESHCONF_HWMP_PREQ_MIN_INTERVAL,
			cur_params.dot11MeshHWMPpreqMinInterval) ||
	    nla_put_u16(msg, NL80211_MESHCONF_HWMP_PERR_MIN_INTERVAL,
			cur_params.dot11MeshHWMPperrMinInterval) ||
	    nla_put_u16(msg, NL80211_MESHCONF_HWMP_NET_DIAM_TRVS_TIME,
			cur_params.dot11MeshHWMPnetDiameterTraversalTime) ||
	    nla_put_u8(msg, NL80211_MESHCONF_HWMP_ROOTMODE,
		       cur_params.dot11MeshHWMPRootMode) ||
	    nla_put_u16(msg, NL80211_MESHCONF_HWMP_RANN_INTERVAL,
			cur_params.dot11MeshHWMPRannInterval) ||
	    nla_put_u8(msg, NL80211_MESHCONF_GATE_ANNOUNCEMENTS,
		       cur_params.dot11MeshGateAnnouncementProtocol) ||
	    nla_put_u8(msg, NL80211_MESHCONF_FORWARDING,
		       cur_params.dot11MeshForwarding) ||
	    nla_put_s32(msg, NL80211_MESHCONF_RSSI_THRESHOLD,
			cur_params.rssi_threshold) ||
	    nla_put_u32(msg, NL80211_MESHCONF_HT_OPMODE,
			cur_params.ht_opmode) ||
	    nla_put_u32(msg, NL80211_MESHCONF_HWMP_PATH_TO_ROOT_TIMEOUT,
			cur_params.dot11MeshHWMPactivePathToRootTimeout) ||
	    nla_put_u16(msg, NL80211_MESHCONF_HWMP_ROOT_INTERVAL,
			cur_params.dot11MeshHWMProotInterval) ||
	    nla_put_u16(msg, NL80211_MESHCONF_HWMP_CONFIRMATION_INTERVAL,
			cur_params.dot11MeshHWMPconfirmationInterval) ||
	    nla_put_u32(msg, NL80211_MESHCONF_POWER_MODE,
			cur_params.power_mode) ||
	    nla_put_u16(msg, NL80211_MESHCONF_AWAKE_WINDOW,
			cur_params.dot11MeshAwakeWindowDuration) ||
	    nla_put_u32(msg, NL80211_MESHCONF_PLINK_TIMEOUT,
			cur_params.plink_timeout) ||
	    nla_put_u8(msg, NL80211_MESHCONF_CONNECTED_TO_GATE,
		       cur_params.dot11MeshConnectedToMeshGate))
		goto nla_put_failure;
	nla_nest_end(msg, pinfoattr);
	genlmsg_end(msg, hdr);
	return genlmsg_reply(msg, info);

 nla_put_failure:
 out:
	nlmsg_free(msg);
	return -ENOBUFS;
}