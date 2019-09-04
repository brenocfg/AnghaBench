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
struct snd_dice {scalar_t__* rx_midi_ports; scalar_t__* tx_midi_ports; int /*<<< orphan*/  rx_pcm_chs; int /*<<< orphan*/  tx_pcm_chs; } ;
struct dice_mytek_spec {int /*<<< orphan*/  rx_pcm_chs; int /*<<< orphan*/  tx_pcm_chs; } ;

/* Variables and functions */
 int MAX_STREAMS ; 
 int SND_DICE_RATE_MODE_COUNT ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct dice_mytek_spec stereo_192_dsd_dac ; 

int snd_dice_detect_mytek_formats(struct snd_dice *dice)
{
	int i;
	const struct dice_mytek_spec *dev;

	dev = &stereo_192_dsd_dac;

	memcpy(dice->tx_pcm_chs, dev->tx_pcm_chs,
	       MAX_STREAMS * SND_DICE_RATE_MODE_COUNT * sizeof(unsigned int));
	memcpy(dice->rx_pcm_chs, dev->rx_pcm_chs,
	       MAX_STREAMS * SND_DICE_RATE_MODE_COUNT * sizeof(unsigned int));

	for (i = 0; i < MAX_STREAMS; ++i) {
		dice->tx_midi_ports[i] = 0;
		dice->rx_midi_ports[i] = 0;
	}

	return 0;
}