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
struct rsi_ps_info {int enabled; int /*<<< orphan*/  deep_sleep_wakeup_period; scalar_t__ num_dtims_per_sleep; scalar_t__ dtim_interval_duration; scalar_t__ num_bcns_per_lis_int; int /*<<< orphan*/  listen_interval; scalar_t__ monitor_interval; scalar_t__ rx_hysterisis; scalar_t__ tx_hysterisis; scalar_t__ rx_threshold; scalar_t__ tx_threshold; int /*<<< orphan*/  sleep_type; } ;
struct rsi_hw {struct rsi_ps_info ps_info; } ;

/* Variables and functions */
 int /*<<< orphan*/  RSI_DEF_DS_WAKEUP_PERIOD ; 
 int /*<<< orphan*/  RSI_DEF_LISTEN_INTERVAL ; 
 int /*<<< orphan*/  RSI_SLEEP_TYPE_LP ; 

void rsi_default_ps_params(struct rsi_hw *adapter)
{
	struct rsi_ps_info *ps_info = &adapter->ps_info;

	ps_info->enabled = true;
	ps_info->sleep_type = RSI_SLEEP_TYPE_LP;
	ps_info->tx_threshold = 0;
	ps_info->rx_threshold = 0;
	ps_info->tx_hysterisis = 0;
	ps_info->rx_hysterisis = 0;
	ps_info->monitor_interval = 0;
	ps_info->listen_interval = RSI_DEF_LISTEN_INTERVAL;
	ps_info->num_bcns_per_lis_int = 0;
	ps_info->dtim_interval_duration = 0;
	ps_info->num_dtims_per_sleep = 0;
	ps_info->deep_sleep_wakeup_period = RSI_DEF_DS_WAKEUP_PERIOD;
}