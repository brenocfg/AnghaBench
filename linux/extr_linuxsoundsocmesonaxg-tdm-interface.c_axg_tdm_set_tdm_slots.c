#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u32 ;
struct snd_soc_dai {int /*<<< orphan*/  dev; TYPE_3__* driver; scalar_t__ capture_dma_data; scalar_t__ playback_dma_data; } ;
struct axg_tdm_stream {int /*<<< orphan*/ * mask; } ;
struct axg_tdm_iface {unsigned int slots; int slot_width; } ;
struct TYPE_5__ {unsigned int channels_max; } ;
struct TYPE_4__ {unsigned int channels_max; } ;
struct TYPE_6__ {TYPE_2__ capture; TYPE_1__ playback; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned int axg_tdm_slots_total (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 struct axg_tdm_iface* snd_soc_dai_get_drvdata (struct snd_soc_dai*) ; 

int axg_tdm_set_tdm_slots(struct snd_soc_dai *dai, u32 *tx_mask,
			  u32 *rx_mask, unsigned int slots,
			  unsigned int slot_width)
{
	struct axg_tdm_iface *iface = snd_soc_dai_get_drvdata(dai);
	struct axg_tdm_stream *tx = (struct axg_tdm_stream *)
		dai->playback_dma_data;
	struct axg_tdm_stream *rx = (struct axg_tdm_stream *)
		dai->capture_dma_data;
	unsigned int tx_slots, rx_slots;

	tx_slots = axg_tdm_slots_total(tx_mask);
	rx_slots = axg_tdm_slots_total(rx_mask);

	/* We should at least have a slot for a valid interface */
	if (!tx_slots && !rx_slots) {
		dev_err(dai->dev, "interface has no slot\n");
		return -EINVAL;
	}

	/*
	 * Amend the dai driver channel number and let dpcm channel merge do
	 * its job
	 */
	if (tx) {
		tx->mask = tx_mask;
		dai->driver->playback.channels_max = tx_slots;
	}

	if (rx) {
		rx->mask = rx_mask;
		dai->driver->capture.channels_max = rx_slots;
	}

	iface->slots = slots;

	switch (slot_width) {
	case 0:
		/* defaults width to 32 if not provided */
		iface->slot_width = 32;
		break;
	case 8:
	case 16:
	case 24:
	case 32:
		iface->slot_width = slot_width;
		break;
	default:
		dev_err(dai->dev, "unsupported slot width: %d\n", slot_width);
		return -EINVAL;
	}

	return 0;
}