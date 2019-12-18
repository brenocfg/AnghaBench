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
struct snd_soc_dai {int dummy; } ;
struct bcm2835_i2s_dev {int tdm_slots; unsigned int rx_mask; unsigned int tx_mask; int slot_width; int frame_length; } ;

/* Variables and functions */
 int BCM2835_I2S_MAX_FRAME_LENGTH ; 
 int EINVAL ; 
 unsigned int GENMASK (int,int /*<<< orphan*/ ) ; 
 int hweight_long (unsigned long) ; 
 struct bcm2835_i2s_dev* snd_soc_dai_get_drvdata (struct snd_soc_dai*) ; 

__attribute__((used)) static int bcm2835_i2s_set_dai_tdm_slot(struct snd_soc_dai *dai,
	unsigned int tx_mask, unsigned int rx_mask,
	int slots, int width)
{
	struct bcm2835_i2s_dev *dev = snd_soc_dai_get_drvdata(dai);

	if (slots) {
		if (slots < 0 || width < 0)
			return -EINVAL;

		/* Limit masks to available slots */
		rx_mask &= GENMASK(slots - 1, 0);
		tx_mask &= GENMASK(slots - 1, 0);

		/*
		 * The driver is limited to 2-channel setups.
		 * Check that exactly 2 bits are set in the masks.
		 */
		if (hweight_long((unsigned long) rx_mask) != 2
		    || hweight_long((unsigned long) tx_mask) != 2)
			return -EINVAL;

		if (slots * width > BCM2835_I2S_MAX_FRAME_LENGTH)
			return -EINVAL;
	}

	dev->tdm_slots = slots;

	dev->rx_mask = rx_mask;
	dev->tx_mask = tx_mask;
	dev->slot_width = width;
	dev->frame_length = slots * width;

	return 0;
}