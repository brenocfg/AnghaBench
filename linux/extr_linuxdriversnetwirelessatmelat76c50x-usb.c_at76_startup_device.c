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
struct at76_card_config {char* short_retry_limit; int encryption_type; int exclude_unencrypted; int auto_rate_fallback; size_t wep_default_key_id; size_t short_preamble; void* beacon_period; int /*<<< orphan*/  wep_default_key_value; int /*<<< orphan*/  ssid_len; int /*<<< orphan*/  current_ssid; scalar_t__ privacy_invoked; int /*<<< orphan*/  channel; int /*<<< orphan*/  basic_rate_set; void* fragmentation_threshold; void* rts_threshold; scalar_t__ promiscuous_mode; } ;
struct at76_priv {scalar_t__ iw_mode; size_t wep_key_id; scalar_t__* wep_keys_len; size_t preamble_type; char* short_retry_limit; scalar_t__ txrate; char* auth_mode; char* scan_max_time; scalar_t__ scan_mode; int scanning; int /*<<< orphan*/  rts_threshold; int /*<<< orphan*/  frag_threshold; int /*<<< orphan*/  bssid; TYPE_1__* hw; struct at76_card_config card_config; int /*<<< orphan*/  udev; int /*<<< orphan*/  beacon_period; int /*<<< orphan*/  wep_keys; int /*<<< orphan*/  essid_size; int /*<<< orphan*/  essid; scalar_t__ wep_enabled; int /*<<< orphan*/  channel; int /*<<< orphan*/  scan_min_time; int /*<<< orphan*/  pm_period; int /*<<< orphan*/  pm_mode; } ;
struct TYPE_2__ {int /*<<< orphan*/  wiphy; } ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_RADIO_ON ; 
 int /*<<< orphan*/  CMD_STARTUP ; 
 int DBG_MIB ; 
 int /*<<< orphan*/  DBG_PARAMS ; 
 int IW_ESSID_MAX_SIZE ; 
 scalar_t__ IW_MODE_ADHOC ; 
 scalar_t__ SCAN_TYPE_ACTIVE ; 
 scalar_t__ TX_RATE_11MBIT ; 
 scalar_t__ TX_RATE_1MBIT ; 
 scalar_t__ TX_RATE_2MBIT ; 
 scalar_t__ TX_RATE_5_5MBIT ; 
 scalar_t__ TX_RATE_AUTO ; 
 scalar_t__ WEP_SMALL_KEY_LEN ; 
 scalar_t__ WLAN_AUTH_OPEN ; 
 int /*<<< orphan*/  at76_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,...) ; 
 int at76_debug ; 
 int /*<<< orphan*/  at76_dump_mib_local (struct at76_priv*) ; 
 int /*<<< orphan*/  at76_dump_mib_mac (struct at76_priv*) ; 
 int /*<<< orphan*/  at76_dump_mib_mac_addr (struct at76_priv*) ; 
 int /*<<< orphan*/  at76_dump_mib_mac_mgmt (struct at76_priv*) ; 
 int /*<<< orphan*/  at76_dump_mib_mac_wep (struct at76_priv*) ; 
 int /*<<< orphan*/  at76_dump_mib_mdomain (struct at76_priv*) ; 
 int /*<<< orphan*/  at76_dump_mib_phy (struct at76_priv*) ; 
 int at76_set_autorate_fallback (struct at76_priv*,int) ; 
 int at76_set_card_command (int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct at76_card_config*,int) ; 
 int at76_set_frag (struct at76_priv*,int /*<<< orphan*/ ) ; 
 int at76_set_pm_mode (struct at76_priv*) ; 
 int at76_set_preamble (struct at76_priv*,size_t) ; 
 int at76_set_radio (struct at76_priv*,int) ; 
 int at76_set_rts (struct at76_priv*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  at76_wait_completion (struct at76_priv*,int /*<<< orphan*/ ) ; 
 void* cpu_to_le16 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eth_zero_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  hw_rates ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memset (struct at76_card_config*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/ * preambles ; 
 int /*<<< orphan*/  wiphy_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  wiphy_name (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int at76_startup_device(struct at76_priv *priv)
{
	struct at76_card_config *ccfg = &priv->card_config;
	int ret;

	at76_dbg(DBG_PARAMS,
		 "%s param: ssid %.*s (%*phD) mode %s ch %d wep %s key %d "
		 "keylen %d", wiphy_name(priv->hw->wiphy), priv->essid_size,
		 priv->essid, IW_ESSID_MAX_SIZE, priv->essid,
		 priv->iw_mode == IW_MODE_ADHOC ? "adhoc" : "infra",
		 priv->channel, priv->wep_enabled ? "enabled" : "disabled",
		 priv->wep_key_id, priv->wep_keys_len[priv->wep_key_id]);
	at76_dbg(DBG_PARAMS,
		 "%s param: preamble %s rts %d retry %d frag %d "
		 "txrate %s auth_mode %d", wiphy_name(priv->hw->wiphy),
		 preambles[priv->preamble_type], priv->rts_threshold,
		 priv->short_retry_limit, priv->frag_threshold,
		 priv->txrate == TX_RATE_1MBIT ? "1MBit" : priv->txrate ==
		 TX_RATE_2MBIT ? "2MBit" : priv->txrate ==
		 TX_RATE_5_5MBIT ? "5.5MBit" : priv->txrate ==
		 TX_RATE_11MBIT ? "11MBit" : priv->txrate ==
		 TX_RATE_AUTO ? "auto" : "<invalid>", priv->auth_mode);
	at76_dbg(DBG_PARAMS,
		 "%s param: pm_mode %d pm_period %d auth_mode %s "
		 "scan_times %d %d scan_mode %s",
		 wiphy_name(priv->hw->wiphy), priv->pm_mode, priv->pm_period,
		 priv->auth_mode == WLAN_AUTH_OPEN ? "open" : "shared_secret",
		 priv->scan_min_time, priv->scan_max_time,
		 priv->scan_mode == SCAN_TYPE_ACTIVE ? "active" : "passive");

	memset(ccfg, 0, sizeof(struct at76_card_config));
	ccfg->promiscuous_mode = 0;
	ccfg->short_retry_limit = priv->short_retry_limit;

	if (priv->wep_enabled) {
		if (priv->wep_keys_len[priv->wep_key_id] > WEP_SMALL_KEY_LEN)
			ccfg->encryption_type = 2;
		else
			ccfg->encryption_type = 1;

		/* jal: always exclude unencrypted if WEP is active */
		ccfg->exclude_unencrypted = 1;
	} else {
		ccfg->exclude_unencrypted = 0;
		ccfg->encryption_type = 0;
	}

	ccfg->rts_threshold = cpu_to_le16(priv->rts_threshold);
	ccfg->fragmentation_threshold = cpu_to_le16(priv->frag_threshold);

	memcpy(ccfg->basic_rate_set, hw_rates, 4);
	/* jal: really needed, we do a set_mib for autorate later ??? */
	ccfg->auto_rate_fallback = (priv->txrate == TX_RATE_AUTO ? 1 : 0);
	ccfg->channel = priv->channel;
	ccfg->privacy_invoked = priv->wep_enabled;
	memcpy(ccfg->current_ssid, priv->essid, IW_ESSID_MAX_SIZE);
	ccfg->ssid_len = priv->essid_size;

	ccfg->wep_default_key_id = priv->wep_key_id;
	memcpy(ccfg->wep_default_key_value, priv->wep_keys,
	       sizeof(priv->wep_keys));

	ccfg->short_preamble = priv->preamble_type;
	ccfg->beacon_period = cpu_to_le16(priv->beacon_period);

	ret = at76_set_card_command(priv->udev, CMD_STARTUP, &priv->card_config,
				    sizeof(struct at76_card_config));
	if (ret < 0) {
		wiphy_err(priv->hw->wiphy, "at76_set_card_command failed: %d\n",
			  ret);
		return ret;
	}

	at76_wait_completion(priv, CMD_STARTUP);

	/* remove BSSID from previous run */
	eth_zero_addr(priv->bssid);

	priv->scanning = false;

	if (at76_set_radio(priv, 1) == 1)
		at76_wait_completion(priv, CMD_RADIO_ON);

	ret = at76_set_preamble(priv, priv->preamble_type);
	if (ret < 0)
		return ret;

	ret = at76_set_frag(priv, priv->frag_threshold);
	if (ret < 0)
		return ret;

	ret = at76_set_rts(priv, priv->rts_threshold);
	if (ret < 0)
		return ret;

	ret = at76_set_autorate_fallback(priv,
					 priv->txrate == TX_RATE_AUTO ? 1 : 0);
	if (ret < 0)
		return ret;

	ret = at76_set_pm_mode(priv);
	if (ret < 0)
		return ret;

	if (at76_debug & DBG_MIB) {
		at76_dump_mib_mac(priv);
		at76_dump_mib_mac_addr(priv);
		at76_dump_mib_mac_mgmt(priv);
		at76_dump_mib_mac_wep(priv);
		at76_dump_mib_mdomain(priv);
		at76_dump_mib_phy(priv);
		at76_dump_mib_local(priv);
	}

	return 0;
}