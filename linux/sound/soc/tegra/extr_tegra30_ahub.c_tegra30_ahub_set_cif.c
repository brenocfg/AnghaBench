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
struct tegra30_ahub_cif_conf {int threshold; int audio_channels; int client_channels; int audio_bits; int client_bits; int expand; int stereo_conv; int replicate; int direction; int truncate; int mono_conv; } ;
struct regmap {int dummy; } ;

/* Variables and functions */
 int TEGRA30_AUDIOCIF_CTRL_AUDIO_BITS_SHIFT ; 
 int TEGRA30_AUDIOCIF_CTRL_AUDIO_CHANNELS_SHIFT ; 
 int TEGRA30_AUDIOCIF_CTRL_CLIENT_BITS_SHIFT ; 
 int TEGRA30_AUDIOCIF_CTRL_CLIENT_CHANNELS_SHIFT ; 
 int TEGRA30_AUDIOCIF_CTRL_DIRECTION_SHIFT ; 
 int TEGRA30_AUDIOCIF_CTRL_EXPAND_SHIFT ; 
 int TEGRA30_AUDIOCIF_CTRL_FIFO_THRESHOLD_SHIFT ; 
 int TEGRA30_AUDIOCIF_CTRL_MONO_CONV_SHIFT ; 
 int TEGRA30_AUDIOCIF_CTRL_REPLICATE_SHIFT ; 
 int TEGRA30_AUDIOCIF_CTRL_STEREO_CONV_SHIFT ; 
 int TEGRA30_AUDIOCIF_CTRL_TRUNCATE_SHIFT ; 
 int /*<<< orphan*/  regmap_write (struct regmap*,unsigned int,unsigned int) ; 

void tegra30_ahub_set_cif(struct regmap *regmap, unsigned int reg,
			  struct tegra30_ahub_cif_conf *conf)
{
	unsigned int value;

	value = (conf->threshold <<
			TEGRA30_AUDIOCIF_CTRL_FIFO_THRESHOLD_SHIFT) |
		((conf->audio_channels - 1) <<
			TEGRA30_AUDIOCIF_CTRL_AUDIO_CHANNELS_SHIFT) |
		((conf->client_channels - 1) <<
			TEGRA30_AUDIOCIF_CTRL_CLIENT_CHANNELS_SHIFT) |
		(conf->audio_bits <<
			TEGRA30_AUDIOCIF_CTRL_AUDIO_BITS_SHIFT) |
		(conf->client_bits <<
			TEGRA30_AUDIOCIF_CTRL_CLIENT_BITS_SHIFT) |
		(conf->expand <<
			TEGRA30_AUDIOCIF_CTRL_EXPAND_SHIFT) |
		(conf->stereo_conv <<
			TEGRA30_AUDIOCIF_CTRL_STEREO_CONV_SHIFT) |
		(conf->replicate <<
			TEGRA30_AUDIOCIF_CTRL_REPLICATE_SHIFT) |
		(conf->direction <<
			TEGRA30_AUDIOCIF_CTRL_DIRECTION_SHIFT) |
		(conf->truncate <<
			TEGRA30_AUDIOCIF_CTRL_TRUNCATE_SHIFT) |
		(conf->mono_conv <<
			TEGRA30_AUDIOCIF_CTRL_MONO_CONV_SHIFT);

	regmap_write(regmap, reg, value);
}