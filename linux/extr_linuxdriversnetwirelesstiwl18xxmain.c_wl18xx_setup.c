#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct wl18xx_static_data_priv {int dummy; } ;
struct TYPE_8__ {scalar_t__ board_type; int low_band_component; int low_band_component_type; int high_band_component; int high_band_component_type; int pwr_limit_reference_11_abg; int number_of_assembled_ant2_4; int number_of_assembled_ant5; int external_pa_dc2dc; } ;
struct TYPE_7__ {scalar_t__ mode; } ;
struct TYPE_9__ {TYPE_3__ phy; TYPE_2__ ht; } ;
struct wl18xx_priv {TYPE_4__ conf; } ;
struct wl18xx_fw_status_priv {int dummy; } ;
struct wl18xx_fw_status {int dummy; } ;
struct wl18xx_acx_statistics {int dummy; } ;
struct TYPE_6__ {int fw_stats_len; } ;
struct wl1271 {int num_rx_desc; int fw_status_len; int fw_status_priv_len; int static_data_priv_len; int enable_11a; int /*<<< orphan*/  dev; TYPE_1__ stats; int /*<<< orphan*/  hw_min_ht_rate; int /*<<< orphan*/  hw_tx_rate_tbl_size; int /*<<< orphan*/  band_rate_to_idx; int /*<<< orphan*/  num_mac_addr; int /*<<< orphan*/  n_iface_combinations; int /*<<< orphan*/  iface_combinations; scalar_t__ max_ap_stations; scalar_t__ num_links; int /*<<< orphan*/  num_tx_desc; int /*<<< orphan*/  rtable; struct wl18xx_priv* priv; } ;
struct TYPE_10__ {int /*<<< orphan*/ * init_vif; int /*<<< orphan*/ * set_rx_csum; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 scalar_t__ BOARD_TYPE_COM8_18XX ; 
 scalar_t__ BOARD_TYPE_DVP_18XX ; 
 scalar_t__ BOARD_TYPE_EVB_18XX ; 
 scalar_t__ BOARD_TYPE_FPGA_18XX ; 
 scalar_t__ BOARD_TYPE_HDK_18XX ; 
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int EINVAL ; 
 scalar_t__ HT_MODE_DEFAULT ; 
 scalar_t__ HT_MODE_SISO20 ; 
 scalar_t__ HT_MODE_WIDE ; 
 int /*<<< orphan*/  NL80211_BAND_2GHZ ; 
 int /*<<< orphan*/  NL80211_BAND_5GHZ ; 
 scalar_t__ NUM_BOARD_TYPES ; 
 int /*<<< orphan*/  WL18XX_CONF_HW_RXTX_RATE_MAX ; 
 int /*<<< orphan*/  WL18XX_CONF_HW_RXTX_RATE_MCS0 ; 
 scalar_t__ WL18XX_CONF_SG_PARAMS_MAX ; 
 scalar_t__ WL18XX_MAX_AP_STATIONS ; 
 scalar_t__ WL18XX_MAX_LINKS ; 
 int /*<<< orphan*/  WL18XX_NUM_MAC_ADDRESSES ; 
 int WL18XX_NUM_RX_DESCRIPTORS ; 
 int /*<<< orphan*/  WL18XX_NUM_TX_DESCRIPTORS ; 
 scalar_t__ WLCORE_CONF_SG_PARAMS_MAX ; 
 scalar_t__ WLCORE_MAX_LINKS ; 
 scalar_t__ board_type_param ; 
 int /*<<< orphan*/  checksum_param ; 
 int dc2dc_param ; 
 int high_band_component_param ; 
 int high_band_component_type_param ; 
 scalar_t__ ht_mode_param ; 
 int low_band_component_param ; 
 int low_band_component_type_param ; 
 int n_antennas_2_param ; 
 int n_antennas_5_param ; 
 int num_rx_desc_param ; 
 int pwr_limit_reference_11_abg_param ; 
 int /*<<< orphan*/  strcmp (scalar_t__,char*) ; 
 int /*<<< orphan*/  wl1271_error (char*,scalar_t__) ; 
 int /*<<< orphan*/  wl18xx_band_rate_to_idx ; 
 int wl18xx_conf_init (struct wl1271*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  wl18xx_iface_combinations ; 
 scalar_t__ wl18xx_is_mimo_supported (struct wl1271*) ; 
 int /*<<< orphan*/  wl18xx_mimo_ht_cap_2ghz ; 
 TYPE_5__ wl18xx_ops ; 
 int /*<<< orphan*/  wl18xx_rtable ; 
 int /*<<< orphan*/  wl18xx_siso20_ht_cap ; 
 int /*<<< orphan*/  wl18xx_siso40_ht_cap_2ghz ; 
 int /*<<< orphan*/  wl18xx_siso40_ht_cap_5ghz ; 
 int /*<<< orphan*/  wlcore_set_ht_cap (struct wl1271*,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int wl18xx_setup(struct wl1271 *wl)
{
	struct wl18xx_priv *priv = wl->priv;
	int ret;

	BUILD_BUG_ON(WL18XX_MAX_LINKS > WLCORE_MAX_LINKS);
	BUILD_BUG_ON(WL18XX_MAX_AP_STATIONS > WL18XX_MAX_LINKS);
	BUILD_BUG_ON(WL18XX_CONF_SG_PARAMS_MAX > WLCORE_CONF_SG_PARAMS_MAX);

	wl->rtable = wl18xx_rtable;
	wl->num_tx_desc = WL18XX_NUM_TX_DESCRIPTORS;
	wl->num_rx_desc = WL18XX_NUM_RX_DESCRIPTORS;
	wl->num_links = WL18XX_MAX_LINKS;
	wl->max_ap_stations = WL18XX_MAX_AP_STATIONS;
	wl->iface_combinations = wl18xx_iface_combinations;
	wl->n_iface_combinations = ARRAY_SIZE(wl18xx_iface_combinations);
	wl->num_mac_addr = WL18XX_NUM_MAC_ADDRESSES;
	wl->band_rate_to_idx = wl18xx_band_rate_to_idx;
	wl->hw_tx_rate_tbl_size = WL18XX_CONF_HW_RXTX_RATE_MAX;
	wl->hw_min_ht_rate = WL18XX_CONF_HW_RXTX_RATE_MCS0;
	wl->fw_status_len = sizeof(struct wl18xx_fw_status);
	wl->fw_status_priv_len = sizeof(struct wl18xx_fw_status_priv);
	wl->stats.fw_stats_len = sizeof(struct wl18xx_acx_statistics);
	wl->static_data_priv_len = sizeof(struct wl18xx_static_data_priv);

	if (num_rx_desc_param != -1)
		wl->num_rx_desc = num_rx_desc_param;

	ret = wl18xx_conf_init(wl, wl->dev);
	if (ret < 0)
		return ret;

	/* If the module param is set, update it in conf */
	if (board_type_param) {
		if (!strcmp(board_type_param, "fpga")) {
			priv->conf.phy.board_type = BOARD_TYPE_FPGA_18XX;
		} else if (!strcmp(board_type_param, "hdk")) {
			priv->conf.phy.board_type = BOARD_TYPE_HDK_18XX;
		} else if (!strcmp(board_type_param, "dvp")) {
			priv->conf.phy.board_type = BOARD_TYPE_DVP_18XX;
		} else if (!strcmp(board_type_param, "evb")) {
			priv->conf.phy.board_type = BOARD_TYPE_EVB_18XX;
		} else if (!strcmp(board_type_param, "com8")) {
			priv->conf.phy.board_type = BOARD_TYPE_COM8_18XX;
		} else {
			wl1271_error("invalid board type '%s'",
				board_type_param);
			return -EINVAL;
		}
	}

	if (priv->conf.phy.board_type >= NUM_BOARD_TYPES) {
		wl1271_error("invalid board type '%d'",
			priv->conf.phy.board_type);
		return -EINVAL;
	}

	if (low_band_component_param != -1)
		priv->conf.phy.low_band_component = low_band_component_param;
	if (low_band_component_type_param != -1)
		priv->conf.phy.low_band_component_type =
			low_band_component_type_param;
	if (high_band_component_param != -1)
		priv->conf.phy.high_band_component = high_band_component_param;
	if (high_band_component_type_param != -1)
		priv->conf.phy.high_band_component_type =
			high_band_component_type_param;
	if (pwr_limit_reference_11_abg_param != -1)
		priv->conf.phy.pwr_limit_reference_11_abg =
			pwr_limit_reference_11_abg_param;
	if (n_antennas_2_param != -1)
		priv->conf.phy.number_of_assembled_ant2_4 = n_antennas_2_param;
	if (n_antennas_5_param != -1)
		priv->conf.phy.number_of_assembled_ant5 = n_antennas_5_param;
	if (dc2dc_param != -1)
		priv->conf.phy.external_pa_dc2dc = dc2dc_param;

	if (ht_mode_param) {
		if (!strcmp(ht_mode_param, "default"))
			priv->conf.ht.mode = HT_MODE_DEFAULT;
		else if (!strcmp(ht_mode_param, "wide"))
			priv->conf.ht.mode = HT_MODE_WIDE;
		else if (!strcmp(ht_mode_param, "siso20"))
			priv->conf.ht.mode = HT_MODE_SISO20;
		else {
			wl1271_error("invalid ht_mode '%s'", ht_mode_param);
			return -EINVAL;
		}
	}

	if (priv->conf.ht.mode == HT_MODE_DEFAULT) {
		/*
		 * Only support mimo with multiple antennas. Fall back to
		 * siso40.
		 */
		if (wl18xx_is_mimo_supported(wl))
			wlcore_set_ht_cap(wl, NL80211_BAND_2GHZ,
					  &wl18xx_mimo_ht_cap_2ghz);
		else
			wlcore_set_ht_cap(wl, NL80211_BAND_2GHZ,
					  &wl18xx_siso40_ht_cap_2ghz);

		/* 5Ghz is always wide */
		wlcore_set_ht_cap(wl, NL80211_BAND_5GHZ,
				  &wl18xx_siso40_ht_cap_5ghz);
	} else if (priv->conf.ht.mode == HT_MODE_WIDE) {
		wlcore_set_ht_cap(wl, NL80211_BAND_2GHZ,
				  &wl18xx_siso40_ht_cap_2ghz);
		wlcore_set_ht_cap(wl, NL80211_BAND_5GHZ,
				  &wl18xx_siso40_ht_cap_5ghz);
	} else if (priv->conf.ht.mode == HT_MODE_SISO20) {
		wlcore_set_ht_cap(wl, NL80211_BAND_2GHZ,
				  &wl18xx_siso20_ht_cap);
		wlcore_set_ht_cap(wl, NL80211_BAND_5GHZ,
				  &wl18xx_siso20_ht_cap);
	}

	if (!checksum_param) {
		wl18xx_ops.set_rx_csum = NULL;
		wl18xx_ops.init_vif = NULL;
	}

	/* Enable 11a Band only if we have 5G antennas */
	wl->enable_11a = (priv->conf.phy.number_of_assembled_ant5 != 0);

	return 0;
}