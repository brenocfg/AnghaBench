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
struct sst_ssp_config {int ssp_mode; int pcm_mode; int /*<<< orphan*/  start_delay; int /*<<< orphan*/  ssp_protocol; int /*<<< orphan*/  fs_width; int /*<<< orphan*/  data_polarity; int /*<<< orphan*/  frame_sync_polarity; int /*<<< orphan*/  fs_frequency; int /*<<< orphan*/  active_slot_map; int /*<<< orphan*/  duplex; int /*<<< orphan*/  slots; int /*<<< orphan*/  bits_per_slot; int /*<<< orphan*/  ssp_id; } ;
struct TYPE_2__ {int mode; int reserved1; int reserved2; int /*<<< orphan*/  start_delay; int /*<<< orphan*/  ssp_protocol; int /*<<< orphan*/  frame_sync_width; int /*<<< orphan*/  data_polarity; int /*<<< orphan*/  frame_sync_polarity; int /*<<< orphan*/  frame_sync_frequency; int /*<<< orphan*/  active_rx_slot_map; int /*<<< orphan*/  active_tx_slot_map; int /*<<< orphan*/  duplex; int /*<<< orphan*/  nb_slots; int /*<<< orphan*/  nb_bits_per_slots; int /*<<< orphan*/  selection; } ;
struct sst_data {TYPE_1__ ssp_cmd; } ;
struct snd_soc_dai {int dummy; } ;

/* Variables and functions */
 struct sst_data* snd_soc_dai_get_drvdata (struct snd_soc_dai*) ; 
 struct sst_ssp_config sst_ssp_configs ; 

void sst_fill_ssp_defaults(struct snd_soc_dai *dai)
{
	const struct sst_ssp_config *config;
	struct sst_data *ctx = snd_soc_dai_get_drvdata(dai);

	config = &sst_ssp_configs;

	ctx->ssp_cmd.selection = config->ssp_id;
	ctx->ssp_cmd.nb_bits_per_slots = config->bits_per_slot;
	ctx->ssp_cmd.nb_slots = config->slots;
	ctx->ssp_cmd.mode = config->ssp_mode | (config->pcm_mode << 1);
	ctx->ssp_cmd.duplex = config->duplex;
	ctx->ssp_cmd.active_tx_slot_map = config->active_slot_map;
	ctx->ssp_cmd.active_rx_slot_map = config->active_slot_map;
	ctx->ssp_cmd.frame_sync_frequency = config->fs_frequency;
	ctx->ssp_cmd.frame_sync_polarity = config->frame_sync_polarity;
	ctx->ssp_cmd.data_polarity = config->data_polarity;
	ctx->ssp_cmd.frame_sync_width = config->fs_width;
	ctx->ssp_cmd.ssp_protocol = config->ssp_protocol;
	ctx->ssp_cmd.start_delay = config->start_delay;
	ctx->ssp_cmd.reserved1 = ctx->ssp_cmd.reserved2 = 0xFF;
}