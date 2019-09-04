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
struct psc_dma {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned int SND_SOC_DAIFMT_I2S ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,struct snd_soc_dai*,unsigned int) ; 
 struct psc_dma* snd_soc_dai_get_drvdata (struct snd_soc_dai*) ; 

__attribute__((used)) static int psc_i2s_set_fmt(struct snd_soc_dai *cpu_dai, unsigned int format)
{
	struct psc_dma *psc_dma = snd_soc_dai_get_drvdata(cpu_dai);
	dev_dbg(psc_dma->dev, "psc_i2s_set_fmt(cpu_dai=%p, format=%i)\n",
				cpu_dai, format);
	return (format == SND_SOC_DAIFMT_I2S) ? 0 : -EINVAL;
}