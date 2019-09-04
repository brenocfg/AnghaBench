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
struct wl1251 {int dummy; } ;
struct acx_bt_wlan_coex_param {int /*<<< orphan*/  bt_hp_respected_num; int /*<<< orphan*/  pta_auto_mode_enable; int /*<<< orphan*/  pa_sd_enable; int /*<<< orphan*/  ack_mode_dual_ant; int /*<<< orphan*/  bt_anti_starvation_cycles; int /*<<< orphan*/  wlan_elp_hp; int /*<<< orphan*/  missed_rx_avalanche; int /*<<< orphan*/  bt_packets_num; int /*<<< orphan*/  wlan_packets_num; int /*<<< orphan*/  max_cts; int /*<<< orphan*/  quiet_cycle_num; int /*<<< orphan*/  afh_leverage_on; int /*<<< orphan*/  signal_type; int /*<<< orphan*/  antenna_type; int /*<<< orphan*/  next_wlan_packet; int /*<<< orphan*/  hp_dm_max_guard_time; int /*<<< orphan*/  wake_up_beacon; int /*<<< orphan*/  next_bt_lp_packet; int /*<<< orphan*/  bt_anti_starvation_period; int /*<<< orphan*/  wlan_cycle_fast; int /*<<< orphan*/  tx_time_bt_hp_fast; int /*<<< orphan*/  rx_time_bt_hp_fast; int /*<<< orphan*/  tx_time_bt_hp; int /*<<< orphan*/  rx_time_bt_hp; int /*<<< orphan*/  sense_disable_timer; int /*<<< orphan*/  wlan_hp_max_time; int /*<<< orphan*/  bt_hp_max_time; int /*<<< orphan*/  min_rate; } ;

/* Variables and functions */
 int /*<<< orphan*/  ACX_SG_CFG ; 
 int /*<<< orphan*/  DEBUG_ACX ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  PTA_ACK_MODE_DEF ; 
 int /*<<< orphan*/  PTA_AFH_LEVERAGE_ON_DEF ; 
 int /*<<< orphan*/  PTA_ALLOW_PA_SD_DEF ; 
 int /*<<< orphan*/  PTA_ANTENNA_TYPE_DEF ; 
 int /*<<< orphan*/  PTA_ANTI_STARVE_NUM_CYCLE_DEF ; 
 int /*<<< orphan*/  PTA_ANTI_STARVE_PERIOD_DEF ; 
 int /*<<< orphan*/  PTA_AUTO_MODE_NO_CTS_DEF ; 
 int /*<<< orphan*/  PTA_BT_HP_MAXTIME_DEF ; 
 int /*<<< orphan*/  PTA_BT_HP_RESPECTED_DEF ; 
 int /*<<< orphan*/  PTA_CYCLE_TIME_FAST_DEF ; 
 int /*<<< orphan*/  PTA_ELP_HP_DEF ; 
 int /*<<< orphan*/  PTA_HPDM_MAX_TIME_DEF ; 
 int /*<<< orphan*/  PTA_MAX_NUM_CTS_DEF ; 
 int /*<<< orphan*/  PTA_NUMBER_OF_BT_PACKETS_DEF ; 
 int /*<<< orphan*/  PTA_NUMBER_OF_WLAN_PACKETS_DEF ; 
 int /*<<< orphan*/  PTA_NUMBER_QUIET_CYCLE_DEF ; 
 int /*<<< orphan*/  PTA_PROTECTIVE_RX_TIME_DEF ; 
 int /*<<< orphan*/  PTA_PROTECTIVE_RX_TIME_FAST_DEF ; 
 int /*<<< orphan*/  PTA_PROTECTIVE_TX_TIME_DEF ; 
 int /*<<< orphan*/  PTA_PROTECTIVE_TX_TIME_FAST_DEF ; 
 int /*<<< orphan*/  PTA_RX_FOR_AVALANCHE_DEF ; 
 int /*<<< orphan*/  PTA_SENSE_DISABLE_TIMER_DEF ; 
 int /*<<< orphan*/  PTA_SIGNALING_TYPE_DEF ; 
 int /*<<< orphan*/  PTA_TIMEOUT_NEXT_BT_LP_PACKET_DEF ; 
 int /*<<< orphan*/  PTA_TIME_BEFORE_BEACON_DEF ; 
 int /*<<< orphan*/  PTA_TIME_OUT_NEXT_WLAN_DEF ; 
 int /*<<< orphan*/  PTA_WLAN_HP_MAX_TIME_DEF ; 
 int /*<<< orphan*/  RATE_INDEX_24MBPS ; 
 int /*<<< orphan*/  kfree (struct acx_bt_wlan_coex_param*) ; 
 struct acx_bt_wlan_coex_param* kzalloc (int,int /*<<< orphan*/ ) ; 
 int wl1251_cmd_configure (struct wl1251*,int /*<<< orphan*/ ,struct acx_bt_wlan_coex_param*,int) ; 
 int /*<<< orphan*/  wl1251_debug (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  wl1251_warning (char*,int) ; 

int wl1251_acx_sg_cfg(struct wl1251 *wl)
{
	struct acx_bt_wlan_coex_param *param;
	int ret;

	wl1251_debug(DEBUG_ACX, "acx sg cfg");

	param = kzalloc(sizeof(*param), GFP_KERNEL);
	if (!param)
		return -ENOMEM;

	/* BT-WLAN coext parameters */
	param->min_rate = RATE_INDEX_24MBPS;
	param->bt_hp_max_time = PTA_BT_HP_MAXTIME_DEF;
	param->wlan_hp_max_time = PTA_WLAN_HP_MAX_TIME_DEF;
	param->sense_disable_timer = PTA_SENSE_DISABLE_TIMER_DEF;
	param->rx_time_bt_hp = PTA_PROTECTIVE_RX_TIME_DEF;
	param->tx_time_bt_hp = PTA_PROTECTIVE_TX_TIME_DEF;
	param->rx_time_bt_hp_fast = PTA_PROTECTIVE_RX_TIME_FAST_DEF;
	param->tx_time_bt_hp_fast = PTA_PROTECTIVE_TX_TIME_FAST_DEF;
	param->wlan_cycle_fast = PTA_CYCLE_TIME_FAST_DEF;
	param->bt_anti_starvation_period = PTA_ANTI_STARVE_PERIOD_DEF;
	param->next_bt_lp_packet = PTA_TIMEOUT_NEXT_BT_LP_PACKET_DEF;
	param->wake_up_beacon = PTA_TIME_BEFORE_BEACON_DEF;
	param->hp_dm_max_guard_time = PTA_HPDM_MAX_TIME_DEF;
	param->next_wlan_packet = PTA_TIME_OUT_NEXT_WLAN_DEF;
	param->antenna_type = PTA_ANTENNA_TYPE_DEF;
	param->signal_type = PTA_SIGNALING_TYPE_DEF;
	param->afh_leverage_on = PTA_AFH_LEVERAGE_ON_DEF;
	param->quiet_cycle_num = PTA_NUMBER_QUIET_CYCLE_DEF;
	param->max_cts = PTA_MAX_NUM_CTS_DEF;
	param->wlan_packets_num = PTA_NUMBER_OF_WLAN_PACKETS_DEF;
	param->bt_packets_num = PTA_NUMBER_OF_BT_PACKETS_DEF;
	param->missed_rx_avalanche = PTA_RX_FOR_AVALANCHE_DEF;
	param->wlan_elp_hp = PTA_ELP_HP_DEF;
	param->bt_anti_starvation_cycles = PTA_ANTI_STARVE_NUM_CYCLE_DEF;
	param->ack_mode_dual_ant = PTA_ACK_MODE_DEF;
	param->pa_sd_enable = PTA_ALLOW_PA_SD_DEF;
	param->pta_auto_mode_enable = PTA_AUTO_MODE_NO_CTS_DEF;
	param->bt_hp_respected_num = PTA_BT_HP_RESPECTED_DEF;

	ret = wl1251_cmd_configure(wl, ACX_SG_CFG, param, sizeof(*param));
	if (ret < 0) {
		wl1251_warning("failed to set sg config: %d", ret);
		goto out;
	}

out:
	kfree(param);
	return ret;
}