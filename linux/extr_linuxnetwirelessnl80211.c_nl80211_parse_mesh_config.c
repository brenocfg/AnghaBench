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
typedef  int u32 ;
typedef  int u16 ;
struct nlattr {int dummy; } ;
struct mesh_config {int ht_opmode; int /*<<< orphan*/  plink_timeout; int /*<<< orphan*/  dot11MeshAwakeWindowDuration; int /*<<< orphan*/  power_mode; int /*<<< orphan*/  dot11MeshHWMPconfirmationInterval; int /*<<< orphan*/  dot11MeshHWMProotInterval; int /*<<< orphan*/  dot11MeshHWMPactivePathToRootTimeout; int /*<<< orphan*/  rssi_threshold; int /*<<< orphan*/  dot11MeshForwarding; int /*<<< orphan*/  dot11MeshGateAnnouncementProtocol; int /*<<< orphan*/  dot11MeshHWMPRannInterval; int /*<<< orphan*/  dot11MeshHWMPRootMode; int /*<<< orphan*/  dot11MeshHWMPnetDiameterTraversalTime; int /*<<< orphan*/  dot11MeshHWMPperrMinInterval; int /*<<< orphan*/  dot11MeshHWMPpreqMinInterval; int /*<<< orphan*/  dot11MeshHWMPactivePathTimeout; int /*<<< orphan*/  min_discovery_timeout; int /*<<< orphan*/  path_refresh_time; int /*<<< orphan*/  dot11MeshHWMPmaxPREQretries; int /*<<< orphan*/  dot11MeshNbrOffsetMaxNeighbor; int /*<<< orphan*/  auto_open_plinks; int /*<<< orphan*/  element_ttl; int /*<<< orphan*/  dot11MeshTTL; int /*<<< orphan*/  dot11MeshMaxRetries; int /*<<< orphan*/  dot11MeshMaxPeerLinks; int /*<<< orphan*/  dot11MeshHoldingTimeout; int /*<<< orphan*/  dot11MeshConfirmTimeout; int /*<<< orphan*/  dot11MeshRetryTimeout; } ;
struct genl_info {int /*<<< orphan*/  extack; int /*<<< orphan*/ * attrs; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int EINVAL ; 
 int IEEE80211_HT_OP_MODE_NON_GF_STA_PRSNT ; 
 int IEEE80211_HT_OP_MODE_NON_HT_STA_PRSNT ; 
 int IEEE80211_HT_OP_MODE_PROTECTION ; 
 size_t NL80211_ATTR_MESH_CONFIG ; 
 int NL80211_MESHCONF_ATTR_MAX ; 
 size_t NL80211_MESHCONF_AUTO_OPEN_PLINKS ; 
 size_t NL80211_MESHCONF_AWAKE_WINDOW ; 
 size_t NL80211_MESHCONF_CONFIRM_TIMEOUT ; 
 size_t NL80211_MESHCONF_ELEMENT_TTL ; 
 size_t NL80211_MESHCONF_FORWARDING ; 
 size_t NL80211_MESHCONF_GATE_ANNOUNCEMENTS ; 
 size_t NL80211_MESHCONF_HOLDING_TIMEOUT ; 
 size_t NL80211_MESHCONF_HT_OPMODE ; 
 size_t NL80211_MESHCONF_HWMP_ACTIVE_PATH_TIMEOUT ; 
 size_t NL80211_MESHCONF_HWMP_CONFIRMATION_INTERVAL ; 
 size_t NL80211_MESHCONF_HWMP_MAX_PREQ_RETRIES ; 
 size_t NL80211_MESHCONF_HWMP_NET_DIAM_TRVS_TIME ; 
 size_t NL80211_MESHCONF_HWMP_PATH_TO_ROOT_TIMEOUT ; 
 size_t NL80211_MESHCONF_HWMP_PERR_MIN_INTERVAL ; 
 size_t NL80211_MESHCONF_HWMP_PREQ_MIN_INTERVAL ; 
 size_t NL80211_MESHCONF_HWMP_RANN_INTERVAL ; 
 size_t NL80211_MESHCONF_HWMP_ROOTMODE ; 
 size_t NL80211_MESHCONF_HWMP_ROOT_INTERVAL ; 
 size_t NL80211_MESHCONF_MAX_PEER_LINKS ; 
 size_t NL80211_MESHCONF_MAX_RETRIES ; 
 size_t NL80211_MESHCONF_MIN_DISCOVERY_TIMEOUT ; 
 size_t NL80211_MESHCONF_PATH_REFRESH_TIME ; 
 size_t NL80211_MESHCONF_PLINK_TIMEOUT ; 
 size_t NL80211_MESHCONF_POWER_MODE ; 
 size_t NL80211_MESHCONF_RETRY_TIMEOUT ; 
 size_t NL80211_MESHCONF_RSSI_THRESHOLD ; 
 size_t NL80211_MESHCONF_SYNC_OFFSET_MAX_NEIGHBOR ; 
 size_t NL80211_MESHCONF_TTL ; 
 int /*<<< orphan*/  NL80211_MESH_POWER_ACTIVE ; 
 int /*<<< orphan*/  NL80211_MESH_POWER_MAX ; 
 scalar_t__ nl80211_check_bool (struct nlattr*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ *) ; 
 scalar_t__ nl80211_check_power_mode (struct nlattr*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ nl80211_check_s32 (struct nlattr*,int,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ nl80211_check_u16 (struct nlattr*,int,int,int /*<<< orphan*/ *) ; 
 scalar_t__ nl80211_check_u32 (struct nlattr*,int,int,int /*<<< orphan*/ *) ; 
 scalar_t__ nl80211_check_u8 (struct nlattr*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nl80211_meshconf_params_policy ; 
 int nla_get_u16 (struct nlattr*) ; 
 scalar_t__ nla_parse_nested (struct nlattr**,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int nl80211_parse_mesh_config(struct genl_info *info,
				     struct mesh_config *cfg,
				     u32 *mask_out)
{
	struct nlattr *tb[NL80211_MESHCONF_ATTR_MAX + 1];
	u32 mask = 0;
	u16 ht_opmode;

#define FILL_IN_MESH_PARAM_IF_SET(tb, cfg, param, min, max, mask, attr, fn) \
do {									    \
	if (tb[attr]) {							    \
		if (fn(tb[attr], min, max, &cfg->param))		    \
			return -EINVAL;					    \
		mask |= (1 << (attr - 1));				    \
	}								    \
} while (0)

	if (!info->attrs[NL80211_ATTR_MESH_CONFIG])
		return -EINVAL;
	if (nla_parse_nested(tb, NL80211_MESHCONF_ATTR_MAX,
			     info->attrs[NL80211_ATTR_MESH_CONFIG],
			     nl80211_meshconf_params_policy, info->extack))
		return -EINVAL;

	/* This makes sure that there aren't more than 32 mesh config
	 * parameters (otherwise our bitfield scheme would not work.) */
	BUILD_BUG_ON(NL80211_MESHCONF_ATTR_MAX > 32);

	/* Fill in the params struct */
	FILL_IN_MESH_PARAM_IF_SET(tb, cfg, dot11MeshRetryTimeout, 1, 255,
				  mask, NL80211_MESHCONF_RETRY_TIMEOUT,
				  nl80211_check_u16);
	FILL_IN_MESH_PARAM_IF_SET(tb, cfg, dot11MeshConfirmTimeout, 1, 255,
				  mask, NL80211_MESHCONF_CONFIRM_TIMEOUT,
				  nl80211_check_u16);
	FILL_IN_MESH_PARAM_IF_SET(tb, cfg, dot11MeshHoldingTimeout, 1, 255,
				  mask, NL80211_MESHCONF_HOLDING_TIMEOUT,
				  nl80211_check_u16);
	FILL_IN_MESH_PARAM_IF_SET(tb, cfg, dot11MeshMaxPeerLinks, 0, 255,
				  mask, NL80211_MESHCONF_MAX_PEER_LINKS,
				  nl80211_check_u16);
	FILL_IN_MESH_PARAM_IF_SET(tb, cfg, dot11MeshMaxRetries, 0, 16,
				  mask, NL80211_MESHCONF_MAX_RETRIES,
				  nl80211_check_u8);
	FILL_IN_MESH_PARAM_IF_SET(tb, cfg, dot11MeshTTL, 1, 255,
				  mask, NL80211_MESHCONF_TTL, nl80211_check_u8);
	FILL_IN_MESH_PARAM_IF_SET(tb, cfg, element_ttl, 1, 255,
				  mask, NL80211_MESHCONF_ELEMENT_TTL,
				  nl80211_check_u8);
	FILL_IN_MESH_PARAM_IF_SET(tb, cfg, auto_open_plinks, 0, 1,
				  mask, NL80211_MESHCONF_AUTO_OPEN_PLINKS,
				  nl80211_check_bool);
	FILL_IN_MESH_PARAM_IF_SET(tb, cfg, dot11MeshNbrOffsetMaxNeighbor,
				  1, 255, mask,
				  NL80211_MESHCONF_SYNC_OFFSET_MAX_NEIGHBOR,
				  nl80211_check_u32);
	FILL_IN_MESH_PARAM_IF_SET(tb, cfg, dot11MeshHWMPmaxPREQretries, 0, 255,
				  mask, NL80211_MESHCONF_HWMP_MAX_PREQ_RETRIES,
				  nl80211_check_u8);
	FILL_IN_MESH_PARAM_IF_SET(tb, cfg, path_refresh_time, 1, 65535,
				  mask, NL80211_MESHCONF_PATH_REFRESH_TIME,
				  nl80211_check_u32);
	FILL_IN_MESH_PARAM_IF_SET(tb, cfg, min_discovery_timeout, 1, 65535,
				  mask, NL80211_MESHCONF_MIN_DISCOVERY_TIMEOUT,
				  nl80211_check_u16);
	FILL_IN_MESH_PARAM_IF_SET(tb, cfg, dot11MeshHWMPactivePathTimeout,
				  1, 65535, mask,
				  NL80211_MESHCONF_HWMP_ACTIVE_PATH_TIMEOUT,
				  nl80211_check_u32);
	FILL_IN_MESH_PARAM_IF_SET(tb, cfg, dot11MeshHWMPpreqMinInterval,
				  1, 65535, mask,
				  NL80211_MESHCONF_HWMP_PREQ_MIN_INTERVAL,
				  nl80211_check_u16);
	FILL_IN_MESH_PARAM_IF_SET(tb, cfg, dot11MeshHWMPperrMinInterval,
				  1, 65535, mask,
				  NL80211_MESHCONF_HWMP_PERR_MIN_INTERVAL,
				  nl80211_check_u16);
	FILL_IN_MESH_PARAM_IF_SET(tb, cfg,
				  dot11MeshHWMPnetDiameterTraversalTime,
				  1, 65535, mask,
				  NL80211_MESHCONF_HWMP_NET_DIAM_TRVS_TIME,
				  nl80211_check_u16);
	FILL_IN_MESH_PARAM_IF_SET(tb, cfg, dot11MeshHWMPRootMode, 0, 4,
				  mask, NL80211_MESHCONF_HWMP_ROOTMODE,
				  nl80211_check_u8);
	FILL_IN_MESH_PARAM_IF_SET(tb, cfg, dot11MeshHWMPRannInterval, 1, 65535,
				  mask, NL80211_MESHCONF_HWMP_RANN_INTERVAL,
				  nl80211_check_u16);
	FILL_IN_MESH_PARAM_IF_SET(tb, cfg,
				  dot11MeshGateAnnouncementProtocol, 0, 1,
				  mask, NL80211_MESHCONF_GATE_ANNOUNCEMENTS,
				  nl80211_check_bool);
	FILL_IN_MESH_PARAM_IF_SET(tb, cfg, dot11MeshForwarding, 0, 1,
				  mask, NL80211_MESHCONF_FORWARDING,
				  nl80211_check_bool);
	FILL_IN_MESH_PARAM_IF_SET(tb, cfg, rssi_threshold, -255, 0,
				  mask, NL80211_MESHCONF_RSSI_THRESHOLD,
				  nl80211_check_s32);
	/*
	 * Check HT operation mode based on
	 * IEEE 802.11-2016 9.4.2.57 HT Operation element.
	 */
	if (tb[NL80211_MESHCONF_HT_OPMODE]) {
		ht_opmode = nla_get_u16(tb[NL80211_MESHCONF_HT_OPMODE]);

		if (ht_opmode & ~(IEEE80211_HT_OP_MODE_PROTECTION |
				  IEEE80211_HT_OP_MODE_NON_GF_STA_PRSNT |
				  IEEE80211_HT_OP_MODE_NON_HT_STA_PRSNT))
			return -EINVAL;

		/* NON_HT_STA bit is reserved, but some programs set it */
		ht_opmode &= ~IEEE80211_HT_OP_MODE_NON_HT_STA_PRSNT;

		cfg->ht_opmode = ht_opmode;
		mask |= (1 << (NL80211_MESHCONF_HT_OPMODE - 1));
	}
	FILL_IN_MESH_PARAM_IF_SET(tb, cfg, dot11MeshHWMPactivePathToRootTimeout,
				  1, 65535, mask,
				  NL80211_MESHCONF_HWMP_PATH_TO_ROOT_TIMEOUT,
				  nl80211_check_u32);
	FILL_IN_MESH_PARAM_IF_SET(tb, cfg, dot11MeshHWMProotInterval, 1, 65535,
				  mask, NL80211_MESHCONF_HWMP_ROOT_INTERVAL,
				  nl80211_check_u16);
	FILL_IN_MESH_PARAM_IF_SET(tb, cfg,
				  dot11MeshHWMPconfirmationInterval,
				  1, 65535, mask,
				  NL80211_MESHCONF_HWMP_CONFIRMATION_INTERVAL,
				  nl80211_check_u16);
	FILL_IN_MESH_PARAM_IF_SET(tb, cfg, power_mode,
				  NL80211_MESH_POWER_ACTIVE,
				  NL80211_MESH_POWER_MAX,
				  mask, NL80211_MESHCONF_POWER_MODE,
				  nl80211_check_power_mode);
	FILL_IN_MESH_PARAM_IF_SET(tb, cfg, dot11MeshAwakeWindowDuration,
				  0, 65535, mask,
				  NL80211_MESHCONF_AWAKE_WINDOW, nl80211_check_u16);
	FILL_IN_MESH_PARAM_IF_SET(tb, cfg, plink_timeout, 0, 0xffffffff,
				  mask, NL80211_MESHCONF_PLINK_TIMEOUT,
				  nl80211_check_u32);
	if (mask_out)
		*mask_out = mask;

	return 0;

#undef FILL_IN_MESH_PARAM_IF_SET
}