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
struct snd_ca0106_details {int spi_dac; } ;
struct snd_ca0106 {TYPE_1__* card; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
#define  PCM_CENTER_LFE_CHANNEL 131 
#define  PCM_FRONT_CHANNEL 130 
#define  PCM_REAR_CHANNEL 129 
#define  PCM_UNKNOWN_CHANNEL 128 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static int snd_ca0106_channel_dac(struct snd_ca0106 *chip,
				  struct snd_ca0106_details *details,
				  int channel_id)
{
	switch (channel_id) {
	case PCM_FRONT_CHANNEL:
		return (details->spi_dac & 0xf000) >> (4 * 3);
	case PCM_REAR_CHANNEL:
		return (details->spi_dac & 0x0f00) >> (4 * 2);
	case PCM_CENTER_LFE_CHANNEL:
		return (details->spi_dac & 0x00f0) >> (4 * 1);
	case PCM_UNKNOWN_CHANNEL:
		return (details->spi_dac & 0x000f) >> (4 * 0);
	default:
		dev_dbg(chip->card->dev, "ca0106: unknown channel_id %d\n",
			   channel_id);
	}
	return 0;
}