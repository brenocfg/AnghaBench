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
struct wilc_vif {struct wilc* wilc; } ;
struct wilc_priv {scalar_t__ hif_drv; } ;
struct wilc {int dummy; } ;
struct net_device {TYPE_1__* ieee80211_ptr; } ;
struct host_if_drv {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  wiphy; } ;

/* Variables and functions */
 unsigned char ACTIVE_SCAN ; 
 unsigned char AUTORATE ; 
 unsigned char AUTO_PROT ; 
 unsigned char DETECT_PROTECT_REPORT ; 
 unsigned char G_MIXED_11B_2_MODE ; 
 unsigned char G_SELF_CTS_PROT ; 
 unsigned char G_SHORT_PREAMBLE ; 
 unsigned char HT_MIXED_MODE ; 
 unsigned char INFRASTRUCTURE ; 
 unsigned char MIMO_MODE ; 
 unsigned char NORMAL_ACK ; 
 unsigned char NO_POWERSAVE ; 
 unsigned char NO_SECURITY ; 
 unsigned char OPEN_SYSTEM ; 
 unsigned char REKEY_DISABLE ; 
 unsigned char RTS_CTS_NONHT_PROT ; 
 unsigned char SITE_SURVEY_OFF ; 
 int /*<<< orphan*/  WID_11G_OPERATING_MODE ; 
 int /*<<< orphan*/  WID_11I_MODE ; 
 int /*<<< orphan*/  WID_11I_PSK ; 
 int /*<<< orphan*/  WID_11N_CURRENT_TX_MCS ; 
 int /*<<< orphan*/  WID_11N_ENABLE ; 
 int /*<<< orphan*/  WID_11N_ERP_PROT_TYPE ; 
 int /*<<< orphan*/  WID_11N_HT_PROT_TYPE ; 
 int /*<<< orphan*/  WID_11N_IMMEDIATE_BA_ENABLED ; 
 int /*<<< orphan*/  WID_11N_OBSS_NONHT_DETECTION ; 
 int /*<<< orphan*/  WID_11N_OPERATING_MODE ; 
 int /*<<< orphan*/  WID_11N_PROT_MECH ; 
 int /*<<< orphan*/  WID_11N_RIFS_PROT_ENABLE ; 
 int /*<<< orphan*/  WID_11N_SMPS_MODE ; 
 int /*<<< orphan*/  WID_11N_TXOP_PROT_DISABLE ; 
 int /*<<< orphan*/  WID_1X_KEY ; 
 int /*<<< orphan*/  WID_1X_SERV_ADDR ; 
 int /*<<< orphan*/  WID_ACK_POLICY ; 
 int /*<<< orphan*/  WID_AUTH_TYPE ; 
 int /*<<< orphan*/  WID_BCAST_SSID ; 
 int /*<<< orphan*/  WID_BEACON_INTERVAL ; 
 int /*<<< orphan*/  WID_BSS_TYPE ; 
 int /*<<< orphan*/  WID_CURRENT_CHANNEL ; 
 int /*<<< orphan*/  WID_CURRENT_TX_RATE ; 
 int /*<<< orphan*/  WID_DTIM_PERIOD ; 
 int /*<<< orphan*/  WID_FRAG_THRESHOLD ; 
 int /*<<< orphan*/  WID_LISTEN_INTERVAL ; 
 int /*<<< orphan*/  WID_PC_TEST_MODE ; 
 int /*<<< orphan*/  WID_POWER_MANAGEMENT ; 
 int /*<<< orphan*/  WID_PREAMBLE ; 
 int /*<<< orphan*/  WID_QOS_ENABLE ; 
 int /*<<< orphan*/  WID_REKEY_PACKET_COUNT ; 
 int /*<<< orphan*/  WID_REKEY_PERIOD ; 
 int /*<<< orphan*/  WID_REKEY_POLICY ; 
 int /*<<< orphan*/  WID_RTS_THRESHOLD ; 
 int /*<<< orphan*/  WID_SCAN_TYPE ; 
 int /*<<< orphan*/  WID_SET_DRV_HANDLER ; 
 int /*<<< orphan*/  WID_SHORT_SLOT_ALLOWED ; 
 int /*<<< orphan*/  WID_SITE_SURVEY ; 
 int /*<<< orphan*/  WID_TX_POWER_LEVEL_11A ; 
 int /*<<< orphan*/  WID_TX_POWER_LEVEL_11B ; 
 int /*<<< orphan*/  WID_USER_CONTROL_ON_TX_POWER ; 
 int /*<<< orphan*/  WID_WEP_KEY_VALUE ; 
 int /*<<< orphan*/  netdev_dbg (struct net_device*,char*,...) ; 
 int /*<<< orphan*/  strcpy (unsigned char*,char*) ; 
 int strlen (unsigned char*) ; 
 int /*<<< orphan*/  wilc_get_chipid (struct wilc*,int) ; 
 int /*<<< orphan*/  wilc_wlan_cfg_set (struct wilc_vif*,int,int /*<<< orphan*/ ,unsigned char*,int,int,int) ; 
 struct wilc_priv* wiphy_priv (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int linux_wlan_init_test_config(struct net_device *dev,
				       struct wilc_vif *vif)
{
	unsigned char c_val[64];
	struct wilc *wilc = vif->wilc;
	struct wilc_priv *priv;
	struct host_if_drv *hif_drv;

	netdev_dbg(dev, "Start configuring Firmware\n");
	priv = wiphy_priv(dev->ieee80211_ptr->wiphy);
	hif_drv = (struct host_if_drv *)priv->hif_drv;
	netdev_dbg(dev, "Host = %p\n", hif_drv);
	wilc_get_chipid(wilc, false);

	*(int *)c_val = 1;

	if (!wilc_wlan_cfg_set(vif, 1, WID_SET_DRV_HANDLER, c_val, 4, 0, 0))
		goto fail;

	c_val[0] = 0;
	if (!wilc_wlan_cfg_set(vif, 0, WID_PC_TEST_MODE, c_val, 1, 0, 0))
		goto fail;

	c_val[0] = INFRASTRUCTURE;
	if (!wilc_wlan_cfg_set(vif, 0, WID_BSS_TYPE, c_val, 1, 0, 0))
		goto fail;

	c_val[0] = AUTORATE;
	if (!wilc_wlan_cfg_set(vif, 0, WID_CURRENT_TX_RATE, c_val, 1, 0, 0))
		goto fail;

	c_val[0] = G_MIXED_11B_2_MODE;
	if (!wilc_wlan_cfg_set(vif, 0, WID_11G_OPERATING_MODE, c_val, 1, 0,
			       0))
		goto fail;

	c_val[0] = 1;
	if (!wilc_wlan_cfg_set(vif, 0, WID_CURRENT_CHANNEL, c_val, 1, 0, 0))
		goto fail;

	c_val[0] = G_SHORT_PREAMBLE;
	if (!wilc_wlan_cfg_set(vif, 0, WID_PREAMBLE, c_val, 1, 0, 0))
		goto fail;

	c_val[0] = AUTO_PROT;
	if (!wilc_wlan_cfg_set(vif, 0, WID_11N_PROT_MECH, c_val, 1, 0, 0))
		goto fail;

	c_val[0] = ACTIVE_SCAN;
	if (!wilc_wlan_cfg_set(vif, 0, WID_SCAN_TYPE, c_val, 1, 0, 0))
		goto fail;

	c_val[0] = SITE_SURVEY_OFF;
	if (!wilc_wlan_cfg_set(vif, 0, WID_SITE_SURVEY, c_val, 1, 0, 0))
		goto fail;

	*((int *)c_val) = 0xffff;
	if (!wilc_wlan_cfg_set(vif, 0, WID_RTS_THRESHOLD, c_val, 2, 0, 0))
		goto fail;

	*((int *)c_val) = 2346;
	if (!wilc_wlan_cfg_set(vif, 0, WID_FRAG_THRESHOLD, c_val, 2, 0, 0))
		goto fail;

	c_val[0] = 0;
	if (!wilc_wlan_cfg_set(vif, 0, WID_BCAST_SSID, c_val, 1, 0, 0))
		goto fail;

	c_val[0] = 1;
	if (!wilc_wlan_cfg_set(vif, 0, WID_QOS_ENABLE, c_val, 1, 0, 0))
		goto fail;

	c_val[0] = NO_POWERSAVE;
	if (!wilc_wlan_cfg_set(vif, 0, WID_POWER_MANAGEMENT, c_val, 1, 0, 0))
		goto fail;

	c_val[0] = NO_SECURITY; /* NO_ENCRYPT, 0x79 */
	if (!wilc_wlan_cfg_set(vif, 0, WID_11I_MODE, c_val, 1, 0, 0))
		goto fail;

	c_val[0] = OPEN_SYSTEM;
	if (!wilc_wlan_cfg_set(vif, 0, WID_AUTH_TYPE, c_val, 1, 0, 0))
		goto fail;

	strcpy(c_val, "123456790abcdef1234567890");
	if (!wilc_wlan_cfg_set(vif, 0, WID_WEP_KEY_VALUE, c_val,
			       (strlen(c_val) + 1), 0, 0))
		goto fail;

	strcpy(c_val, "12345678");
	if (!wilc_wlan_cfg_set(vif, 0, WID_11I_PSK, c_val, (strlen(c_val)), 0,
			       0))
		goto fail;

	strcpy(c_val, "password");
	if (!wilc_wlan_cfg_set(vif, 0, WID_1X_KEY, c_val, (strlen(c_val) + 1),
			       0, 0))
		goto fail;

	c_val[0] = 192;
	c_val[1] = 168;
	c_val[2] = 1;
	c_val[3] = 112;
	if (!wilc_wlan_cfg_set(vif, 0, WID_1X_SERV_ADDR, c_val, 4, 0, 0))
		goto fail;

	c_val[0] = 3;
	if (!wilc_wlan_cfg_set(vif, 0, WID_LISTEN_INTERVAL, c_val, 1, 0, 0))
		goto fail;

	c_val[0] = 3;
	if (!wilc_wlan_cfg_set(vif, 0, WID_DTIM_PERIOD, c_val, 1, 0, 0))
		goto fail;

	c_val[0] = NORMAL_ACK;
	if (!wilc_wlan_cfg_set(vif, 0, WID_ACK_POLICY, c_val, 1, 0, 0))
		goto fail;

	c_val[0] = 0;
	if (!wilc_wlan_cfg_set(vif, 0, WID_USER_CONTROL_ON_TX_POWER, c_val, 1,
			       0, 0))
		goto fail;

	c_val[0] = 48;
	if (!wilc_wlan_cfg_set(vif, 0, WID_TX_POWER_LEVEL_11A, c_val, 1, 0,
			       0))
		goto fail;

	c_val[0] = 28;
	if (!wilc_wlan_cfg_set(vif, 0, WID_TX_POWER_LEVEL_11B, c_val, 1, 0,
			       0))
		goto fail;

	*((int *)c_val) = 100;
	if (!wilc_wlan_cfg_set(vif, 0, WID_BEACON_INTERVAL, c_val, 2, 0, 0))
		goto fail;

	c_val[0] = REKEY_DISABLE;
	if (!wilc_wlan_cfg_set(vif, 0, WID_REKEY_POLICY, c_val, 1, 0, 0))
		goto fail;

	*((int *)c_val) = 84600;
	if (!wilc_wlan_cfg_set(vif, 0, WID_REKEY_PERIOD, c_val, 4, 0, 0))
		goto fail;

	*((int *)c_val) = 500;
	if (!wilc_wlan_cfg_set(vif, 0, WID_REKEY_PACKET_COUNT, c_val, 4, 0,
			       0))
		goto fail;

	c_val[0] = 1;
	if (!wilc_wlan_cfg_set(vif, 0, WID_SHORT_SLOT_ALLOWED, c_val, 1, 0,
			       0))
		goto fail;

	c_val[0] = G_SELF_CTS_PROT;
	if (!wilc_wlan_cfg_set(vif, 0, WID_11N_ERP_PROT_TYPE, c_val, 1, 0, 0))
		goto fail;

	c_val[0] = 1;
	if (!wilc_wlan_cfg_set(vif, 0, WID_11N_ENABLE, c_val, 1, 0, 0))
		goto fail;

	c_val[0] = HT_MIXED_MODE;
	if (!wilc_wlan_cfg_set(vif, 0, WID_11N_OPERATING_MODE, c_val, 1, 0,
			       0))
		goto fail;

	c_val[0] = 1;
	if (!wilc_wlan_cfg_set(vif, 0, WID_11N_TXOP_PROT_DISABLE, c_val, 1, 0,
			       0))
		goto fail;

	c_val[0] = DETECT_PROTECT_REPORT;
	if (!wilc_wlan_cfg_set(vif, 0, WID_11N_OBSS_NONHT_DETECTION, c_val, 1,
			       0, 0))
		goto fail;

	c_val[0] = RTS_CTS_NONHT_PROT;
	if (!wilc_wlan_cfg_set(vif, 0, WID_11N_HT_PROT_TYPE, c_val, 1, 0, 0))
		goto fail;

	c_val[0] = 0;
	if (!wilc_wlan_cfg_set(vif, 0, WID_11N_RIFS_PROT_ENABLE, c_val, 1, 0,
			       0))
		goto fail;

	c_val[0] = MIMO_MODE;
	if (!wilc_wlan_cfg_set(vif, 0, WID_11N_SMPS_MODE, c_val, 1, 0, 0))
		goto fail;

	c_val[0] = 7;
	if (!wilc_wlan_cfg_set(vif, 0, WID_11N_CURRENT_TX_MCS, c_val, 1, 0,
			       0))
		goto fail;

	c_val[0] = 1;
	if (!wilc_wlan_cfg_set(vif, 0, WID_11N_IMMEDIATE_BA_ENABLED, c_val, 1,
			       1, 1))
		goto fail;

	return 0;

fail:
	return -1;
}