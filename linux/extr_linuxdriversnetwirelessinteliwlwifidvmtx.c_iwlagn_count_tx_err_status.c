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
typedef  int u16 ;
struct TYPE_2__ {int /*<<< orphan*/  unknown; int /*<<< orphan*/  sta_color_mismatch; int /*<<< orphan*/  fail_hw_drop; int /*<<< orphan*/  insuff_cf_poll; int /*<<< orphan*/  fifo_flush; int /*<<< orphan*/  tid_disable; int /*<<< orphan*/  frag_drop; int /*<<< orphan*/  sta_invalid; int /*<<< orphan*/  bt_retry; int /*<<< orphan*/  host_abort; int /*<<< orphan*/  dest_ps; int /*<<< orphan*/  life_expire; int /*<<< orphan*/  rfkill_flush; int /*<<< orphan*/  drain_flow; int /*<<< orphan*/  fifo_underrun; int /*<<< orphan*/  long_limit; int /*<<< orphan*/  short_limit; int /*<<< orphan*/  int_crossed_retry; int /*<<< orphan*/  pp_calc_ttak; int /*<<< orphan*/  pp_quiet_period; int /*<<< orphan*/  pp_bt_prio; int /*<<< orphan*/  pp_few_bytes; int /*<<< orphan*/  pp_delay; } ;
struct iwl_priv {TYPE_1__ reply_tx_stats; } ;

/* Variables and functions */
#define  TX_STATUS_FAIL_BT_RETRY 149 
#define  TX_STATUS_FAIL_DEST_PS 148 
#define  TX_STATUS_FAIL_DRAIN_FLOW 147 
#define  TX_STATUS_FAIL_FIFO_FLUSHED 146 
#define  TX_STATUS_FAIL_FIFO_UNDERRUN 145 
#define  TX_STATUS_FAIL_FRAG_DROPPED 144 
#define  TX_STATUS_FAIL_HOST_ABORTED 143 
#define  TX_STATUS_FAIL_INSUFFICIENT_CF_POLL 142 
#define  TX_STATUS_FAIL_INTERNAL_CROSSED_RETRY 141 
#define  TX_STATUS_FAIL_LIFE_EXPIRE 140 
#define  TX_STATUS_FAIL_LONG_LIMIT 139 
#define  TX_STATUS_FAIL_NO_BEACON_ON_RADAR 138 
#define  TX_STATUS_FAIL_PASSIVE_NO_RX 137 
#define  TX_STATUS_FAIL_RFKILL_FLUSH 136 
#define  TX_STATUS_FAIL_SHORT_LIMIT 135 
#define  TX_STATUS_FAIL_STA_INVALID 134 
#define  TX_STATUS_FAIL_TID_DISABLE 133 
 int TX_STATUS_MSK ; 
#define  TX_STATUS_POSTPONE_BT_PRIO 132 
#define  TX_STATUS_POSTPONE_CALC_TTAK 131 
#define  TX_STATUS_POSTPONE_DELAY 130 
#define  TX_STATUS_POSTPONE_FEW_BYTES 129 
#define  TX_STATUS_POSTPONE_QUIET_PERIOD 128 

__attribute__((used)) static void iwlagn_count_tx_err_status(struct iwl_priv *priv, u16 status)
{
	status &= TX_STATUS_MSK;

	switch (status) {
	case TX_STATUS_POSTPONE_DELAY:
		priv->reply_tx_stats.pp_delay++;
		break;
	case TX_STATUS_POSTPONE_FEW_BYTES:
		priv->reply_tx_stats.pp_few_bytes++;
		break;
	case TX_STATUS_POSTPONE_BT_PRIO:
		priv->reply_tx_stats.pp_bt_prio++;
		break;
	case TX_STATUS_POSTPONE_QUIET_PERIOD:
		priv->reply_tx_stats.pp_quiet_period++;
		break;
	case TX_STATUS_POSTPONE_CALC_TTAK:
		priv->reply_tx_stats.pp_calc_ttak++;
		break;
	case TX_STATUS_FAIL_INTERNAL_CROSSED_RETRY:
		priv->reply_tx_stats.int_crossed_retry++;
		break;
	case TX_STATUS_FAIL_SHORT_LIMIT:
		priv->reply_tx_stats.short_limit++;
		break;
	case TX_STATUS_FAIL_LONG_LIMIT:
		priv->reply_tx_stats.long_limit++;
		break;
	case TX_STATUS_FAIL_FIFO_UNDERRUN:
		priv->reply_tx_stats.fifo_underrun++;
		break;
	case TX_STATUS_FAIL_DRAIN_FLOW:
		priv->reply_tx_stats.drain_flow++;
		break;
	case TX_STATUS_FAIL_RFKILL_FLUSH:
		priv->reply_tx_stats.rfkill_flush++;
		break;
	case TX_STATUS_FAIL_LIFE_EXPIRE:
		priv->reply_tx_stats.life_expire++;
		break;
	case TX_STATUS_FAIL_DEST_PS:
		priv->reply_tx_stats.dest_ps++;
		break;
	case TX_STATUS_FAIL_HOST_ABORTED:
		priv->reply_tx_stats.host_abort++;
		break;
	case TX_STATUS_FAIL_BT_RETRY:
		priv->reply_tx_stats.bt_retry++;
		break;
	case TX_STATUS_FAIL_STA_INVALID:
		priv->reply_tx_stats.sta_invalid++;
		break;
	case TX_STATUS_FAIL_FRAG_DROPPED:
		priv->reply_tx_stats.frag_drop++;
		break;
	case TX_STATUS_FAIL_TID_DISABLE:
		priv->reply_tx_stats.tid_disable++;
		break;
	case TX_STATUS_FAIL_FIFO_FLUSHED:
		priv->reply_tx_stats.fifo_flush++;
		break;
	case TX_STATUS_FAIL_INSUFFICIENT_CF_POLL:
		priv->reply_tx_stats.insuff_cf_poll++;
		break;
	case TX_STATUS_FAIL_PASSIVE_NO_RX:
		priv->reply_tx_stats.fail_hw_drop++;
		break;
	case TX_STATUS_FAIL_NO_BEACON_ON_RADAR:
		priv->reply_tx_stats.sta_color_mismatch++;
		break;
	default:
		priv->reply_tx_stats.unknown++;
		break;
	}
}