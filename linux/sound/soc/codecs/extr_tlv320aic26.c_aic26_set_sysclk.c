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
struct snd_soc_dai {struct snd_soc_component* component; } ;
struct snd_soc_component {int dummy; } ;
struct aic26 {unsigned int mclk; TYPE_1__* spi; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,struct snd_soc_dai*,int,unsigned int,int) ; 
 struct aic26* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 

__attribute__((used)) static int aic26_set_sysclk(struct snd_soc_dai *codec_dai,
			    int clk_id, unsigned int freq, int dir)
{
	struct snd_soc_component *component = codec_dai->component;
	struct aic26 *aic26 = snd_soc_component_get_drvdata(component);

	dev_dbg(&aic26->spi->dev, "aic26_set_sysclk(dai=%p, clk_id==%i,"
		" freq=%i, dir=%i)\n",
		codec_dai, clk_id, freq, dir);

	/* MCLK needs to fall between 2MHz and 50 MHz */
	if ((freq < 2000000) || (freq > 50000000))
		return -EINVAL;

	aic26->mclk = freq;
	return 0;
}