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
typedef  scalar_t__ uint8_t ;
typedef  int u8 ;
struct lbs_private {scalar_t__ channel; } ;
struct TYPE_2__ {void* size; } ;
struct cmd_ds_802_11_rf_channel {void* channel; void* action; TYPE_1__ hdr; } ;
typedef  int /*<<< orphan*/  cmd ;

/* Variables and functions */
 int /*<<< orphan*/  CMD_802_11_RF_CHANNEL ; 
 int CMD_OPT_802_11_RF_CHANNEL_SET ; 
 void* cpu_to_le16 (int) ; 
 int lbs_cmd_with_response (struct lbs_private*,int /*<<< orphan*/ ,struct cmd_ds_802_11_rf_channel*) ; 
 int /*<<< orphan*/  lbs_deb_cmd (char*,int /*<<< orphan*/ ,scalar_t__) ; 
 scalar_t__ le16_to_cpu (void*) ; 
 int /*<<< orphan*/  memset (struct cmd_ds_802_11_rf_channel*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  old_channel ; 

int lbs_set_channel(struct lbs_private *priv, u8 channel)
{
	struct cmd_ds_802_11_rf_channel cmd;
#ifdef DEBUG
	u8 old_channel = priv->channel;
#endif
	int ret = 0;

	memset(&cmd, 0, sizeof(cmd));
	cmd.hdr.size = cpu_to_le16(sizeof(cmd));
	cmd.action = cpu_to_le16(CMD_OPT_802_11_RF_CHANNEL_SET);
	cmd.channel = cpu_to_le16(channel);

	ret = lbs_cmd_with_response(priv, CMD_802_11_RF_CHANNEL, &cmd);
	if (ret)
		goto out;

	priv->channel = (uint8_t) le16_to_cpu(cmd.channel);
	lbs_deb_cmd("channel switch from %d to %d\n", old_channel,
		priv->channel);

out:
	return ret;
}