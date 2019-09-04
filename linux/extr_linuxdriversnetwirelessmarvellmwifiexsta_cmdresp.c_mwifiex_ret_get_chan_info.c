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
struct mwifiex_private {int dummy; } ;
struct mwifiex_channel_band {int /*<<< orphan*/  channel; int /*<<< orphan*/  band_config; } ;
struct mwifiex_band_config {int dummy; } ;
struct host_cmd_tlv_channel_band {int /*<<< orphan*/  channel; int /*<<< orphan*/  band_config; } ;
struct host_cmd_ds_sta_configure {scalar_t__ tlv_buffer; } ;
struct TYPE_2__ {struct host_cmd_ds_sta_configure sta_cfg; } ;
struct host_cmd_ds_command {TYPE_1__ params; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static int mwifiex_ret_get_chan_info(struct mwifiex_private *priv,
				     struct host_cmd_ds_command *resp,
				     struct mwifiex_channel_band *channel_band)
{
	struct host_cmd_ds_sta_configure *sta_cfg_cmd = &resp->params.sta_cfg;
	struct host_cmd_tlv_channel_band *tlv_band_channel;

	tlv_band_channel =
	(struct host_cmd_tlv_channel_band *)sta_cfg_cmd->tlv_buffer;
	memcpy(&channel_band->band_config, &tlv_band_channel->band_config,
	       sizeof(struct mwifiex_band_config));
	channel_band->channel = tlv_band_channel->channel;

	return 0;
}