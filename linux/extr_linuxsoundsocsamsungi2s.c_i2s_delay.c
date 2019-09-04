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
typedef  int u32 ;
struct snd_soc_dai {int /*<<< orphan*/  dev; } ;
struct snd_pcm_substream {scalar_t__ stream; } ;
struct samsung_i2s_variant_regs {int ftx0cnt_off; } ;
struct i2s_dai {scalar_t__ addr; struct samsung_i2s_variant_regs* variant_regs; } ;
typedef  int snd_pcm_sframes_t ;

/* Variables and functions */
 int FICS_TXCOUNT (int) ; 
 int FIC_RXCOUNT (int) ; 
 scalar_t__ I2SFIC ; 
 scalar_t__ I2SFICS ; 
 scalar_t__ SNDRV_PCM_STREAM_CAPTURE ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 scalar_t__ is_secondary (struct i2s_dai*) ; 
 int /*<<< orphan*/  pm_runtime_active (int /*<<< orphan*/ ) ; 
 int readl (scalar_t__) ; 
 struct i2s_dai* to_info (struct snd_soc_dai*) ; 

__attribute__((used)) static snd_pcm_sframes_t
i2s_delay(struct snd_pcm_substream *substream, struct snd_soc_dai *dai)
{
	struct i2s_dai *i2s = to_info(dai);
	u32 reg = readl(i2s->addr + I2SFIC);
	snd_pcm_sframes_t delay;
	const struct samsung_i2s_variant_regs *i2s_regs = i2s->variant_regs;

	WARN_ON(!pm_runtime_active(dai->dev));

	if (substream->stream == SNDRV_PCM_STREAM_CAPTURE)
		delay = FIC_RXCOUNT(reg);
	else if (is_secondary(i2s))
		delay = FICS_TXCOUNT(readl(i2s->addr + I2SFICS));
	else
		delay = (reg >> i2s_regs->ftx0cnt_off) & 0x7f;

	return delay;
}