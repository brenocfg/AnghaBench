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
typedef  int u8 ;
typedef  scalar_t__ u16 ;
struct mwifiex_private {int /*<<< orphan*/  adapter; } ;
struct ieee80211_channel {int band; int /*<<< orphan*/  center_freq; } ;
struct host_cmd_ds_remain_on_chan {int band_cfg; int status; int /*<<< orphan*/  duration; int /*<<< orphan*/  channel; int /*<<< orphan*/  action; } ;
typedef  int /*<<< orphan*/  roc_cfg ;

/* Variables and functions */
 int /*<<< orphan*/  ERROR ; 
 scalar_t__ HostCmd_ACT_GEN_SET ; 
 int /*<<< orphan*/  HostCmd_CMD_REMAIN_ON_CHAN ; 
 int /*<<< orphan*/  NL80211_CHAN_NO_HT ; 
 int /*<<< orphan*/  cpu_to_le16 (scalar_t__) ; 
 int /*<<< orphan*/  cpu_to_le32 (unsigned int) ; 
 int /*<<< orphan*/  ieee80211_frequency_to_channel (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memset (struct host_cmd_ds_remain_on_chan*,int /*<<< orphan*/ ,int) ; 
 int mwifiex_chan_type_to_sec_chan_offset (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mwifiex_dbg (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ mwifiex_send_cmd (struct mwifiex_private*,int /*<<< orphan*/ ,scalar_t__,int /*<<< orphan*/ ,struct host_cmd_ds_remain_on_chan*,int) ; 

int
mwifiex_remain_on_chan_cfg(struct mwifiex_private *priv, u16 action,
			   struct ieee80211_channel *chan,
			   unsigned int duration)
{
	struct host_cmd_ds_remain_on_chan roc_cfg;
	u8 sc;

	memset(&roc_cfg, 0, sizeof(roc_cfg));
	roc_cfg.action = cpu_to_le16(action);
	if (action == HostCmd_ACT_GEN_SET) {
		roc_cfg.band_cfg = chan->band;
		sc = mwifiex_chan_type_to_sec_chan_offset(NL80211_CHAN_NO_HT);
		roc_cfg.band_cfg |= (sc << 2);

		roc_cfg.channel =
			ieee80211_frequency_to_channel(chan->center_freq);
		roc_cfg.duration = cpu_to_le32(duration);
	}
	if (mwifiex_send_cmd(priv, HostCmd_CMD_REMAIN_ON_CHAN,
			     action, 0, &roc_cfg, true)) {
		mwifiex_dbg(priv->adapter, ERROR,
			    "failed to remain on channel\n");
		return -1;
	}

	return roc_cfg.status;
}