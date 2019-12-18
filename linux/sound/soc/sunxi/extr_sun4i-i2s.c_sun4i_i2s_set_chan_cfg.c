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
struct sun4i_i2s {int /*<<< orphan*/  regmap; } ;
struct snd_pcm_hw_params {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  SUN4I_I2S_CHAN_SEL (unsigned int) ; 
 int /*<<< orphan*/  SUN4I_I2S_CHAN_SEL_MASK ; 
 int /*<<< orphan*/  SUN4I_I2S_RX_CHAN_MAP_REG ; 
 int /*<<< orphan*/  SUN4I_I2S_RX_CHAN_SEL_REG ; 
 int /*<<< orphan*/  SUN4I_I2S_TX_CHAN_MAP_REG ; 
 int /*<<< orphan*/  SUN4I_I2S_TX_CHAN_SEL_REG ; 
 unsigned int params_channels (struct snd_pcm_hw_params const*) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int sun4i_i2s_set_chan_cfg(const struct sun4i_i2s *i2s,
				  const struct snd_pcm_hw_params *params)
{
	unsigned int channels = params_channels(params);

	/* Map the channels for playback and capture */
	regmap_write(i2s->regmap, SUN4I_I2S_TX_CHAN_MAP_REG, 0x76543210);
	regmap_write(i2s->regmap, SUN4I_I2S_RX_CHAN_MAP_REG, 0x00003210);

	/* Configure the channels */
	regmap_update_bits(i2s->regmap, SUN4I_I2S_TX_CHAN_SEL_REG,
			   SUN4I_I2S_CHAN_SEL_MASK,
			   SUN4I_I2S_CHAN_SEL(channels));
	regmap_update_bits(i2s->regmap, SUN4I_I2S_RX_CHAN_SEL_REG,
			   SUN4I_I2S_CHAN_SEL_MASK,
			   SUN4I_I2S_CHAN_SEL(channels));

	return 0;
}