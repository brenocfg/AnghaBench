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
struct TYPE_2__ {int nb_slots; unsigned int active_tx_slot_map; unsigned int active_rx_slot_map; int nb_bits_per_slots; } ;
struct sst_data {TYPE_1__ ssp_cmd; } ;
struct snd_soc_dai {int dummy; } ;

/* Variables and functions */
 struct sst_data* snd_soc_dai_get_drvdata (struct snd_soc_dai*) ; 

int sst_fill_ssp_slot(struct snd_soc_dai *dai, unsigned int tx_mask,
		unsigned int rx_mask, int slots, int slot_width)
{
	struct sst_data *ctx = snd_soc_dai_get_drvdata(dai);

	ctx->ssp_cmd.nb_slots = slots;
	ctx->ssp_cmd.active_tx_slot_map = tx_mask;
	ctx->ssp_cmd.active_rx_slot_map = rx_mask;
	ctx->ssp_cmd.nb_bits_per_slots = slot_width;

	return 0;
}