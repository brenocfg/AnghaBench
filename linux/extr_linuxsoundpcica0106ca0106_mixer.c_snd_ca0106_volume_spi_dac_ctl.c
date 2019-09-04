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
struct snd_kcontrol_new {char* name; int private_value; int /*<<< orphan*/  put; int /*<<< orphan*/  get; int /*<<< orphan*/  info; int /*<<< orphan*/  access; int /*<<< orphan*/  iface; int /*<<< orphan*/  member_0; } ;
struct snd_ca0106_details {int spi_dac; } ;

/* Variables and functions */
#define  PCM_CENTER_LFE_CHANNEL 131 
#define  PCM_FRONT_CHANNEL 130 
#define  PCM_REAR_CHANNEL 129 
#define  PCM_UNKNOWN_CHANNEL 128 
 int /*<<< orphan*/  SNDRV_CTL_ELEM_ACCESS_READWRITE ; 
 int /*<<< orphan*/  SNDRV_CTL_ELEM_IFACE_MIXER ; 
 int SPI_REG_SHIFT ; 
 int* spi_dmute_bit ; 
 int* spi_dmute_reg ; 
 int /*<<< orphan*/  spi_mute_get ; 
 int /*<<< orphan*/  spi_mute_info ; 
 int /*<<< orphan*/  spi_mute_put ; 

__attribute__((used)) static struct snd_kcontrol_new
snd_ca0106_volume_spi_dac_ctl(struct snd_ca0106_details *details,
			      int channel_id)
{
	struct snd_kcontrol_new spi_switch = {0};
	int reg, bit;
	int dac_id;

	spi_switch.iface = SNDRV_CTL_ELEM_IFACE_MIXER;
	spi_switch.access = SNDRV_CTL_ELEM_ACCESS_READWRITE;
	spi_switch.info = spi_mute_info;
	spi_switch.get = spi_mute_get;
	spi_switch.put = spi_mute_put;

	switch (channel_id) {
	case PCM_FRONT_CHANNEL:
		spi_switch.name = "Analog Front Playback Switch";
		dac_id = (details->spi_dac & 0xf000) >> (4 * 3);
		break;
	case PCM_REAR_CHANNEL:
		spi_switch.name = "Analog Rear Playback Switch";
		dac_id = (details->spi_dac & 0x0f00) >> (4 * 2);
		break;
	case PCM_CENTER_LFE_CHANNEL:
		spi_switch.name = "Analog Center/LFE Playback Switch";
		dac_id = (details->spi_dac & 0x00f0) >> (4 * 1);
		break;
	case PCM_UNKNOWN_CHANNEL:
		spi_switch.name = "Analog Side Playback Switch";
		dac_id = (details->spi_dac & 0x000f) >> (4 * 0);
		break;
	default:
		/* Unused channel */
		spi_switch.name = NULL;
		dac_id = 0;
	}
	reg = spi_dmute_reg[dac_id];
	bit = spi_dmute_bit[dac_id];

	spi_switch.private_value = (reg << SPI_REG_SHIFT) | bit;

	return spi_switch;
}