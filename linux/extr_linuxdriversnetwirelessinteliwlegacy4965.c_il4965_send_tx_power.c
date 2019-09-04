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
typedef  int u8 ;
struct TYPE_2__ {int flags; int /*<<< orphan*/  channel; } ;
struct il_priv {scalar_t__ band; TYPE_1__ active; int /*<<< orphan*/  status; } ;
struct il4965_txpowertable_cmd {int band; int /*<<< orphan*/  tx_power; int /*<<< orphan*/  channel; int /*<<< orphan*/  member_0; } ;
typedef  int /*<<< orphan*/  cmd ;

/* Variables and functions */
 int /*<<< orphan*/  C_TX_PWR_TBL ; 
 int EAGAIN ; 
 scalar_t__ NL80211_BAND_2GHZ ; 
 int RXON_FLG_CTRL_CHANNEL_LOC_HI_MSK ; 
 int /*<<< orphan*/  S_SCAN_HW ; 
 scalar_t__ WARN_ONCE (int /*<<< orphan*/ ,char*) ; 
 int il4965_fill_txpower_tbl (struct il_priv*,int,int /*<<< orphan*/ ,int,int,int /*<<< orphan*/ *) ; 
 int il_send_cmd_pdu (struct il_priv*,int /*<<< orphan*/ ,int,struct il4965_txpowertable_cmd*) ; 
 int iw4965_is_ht40_channel (int) ; 
 int /*<<< orphan*/  le16_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

__attribute__((used)) static int
il4965_send_tx_power(struct il_priv *il)
{
	struct il4965_txpowertable_cmd cmd = { 0 };
	int ret;
	u8 band = 0;
	bool is_ht40 = false;
	u8 ctrl_chan_high = 0;

	if (WARN_ONCE
	    (test_bit(S_SCAN_HW, &il->status),
	     "TX Power requested while scanning!\n"))
		return -EAGAIN;

	band = il->band == NL80211_BAND_2GHZ;

	is_ht40 = iw4965_is_ht40_channel(il->active.flags);

	if (is_ht40 && (il->active.flags & RXON_FLG_CTRL_CHANNEL_LOC_HI_MSK))
		ctrl_chan_high = 1;

	cmd.band = band;
	cmd.channel = il->active.channel;

	ret =
	    il4965_fill_txpower_tbl(il, band, le16_to_cpu(il->active.channel),
				    is_ht40, ctrl_chan_high, &cmd.tx_power);
	if (ret)
		goto out;

	ret = il_send_cmd_pdu(il, C_TX_PWR_TBL, sizeof(cmd), &cmd);

out:
	return ret;
}