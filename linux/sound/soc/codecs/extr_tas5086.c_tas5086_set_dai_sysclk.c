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
struct tas5086_private {unsigned int mclk; unsigned int sclk; } ;
struct snd_soc_dai {struct snd_soc_component* component; } ;
struct snd_soc_component {int dummy; } ;

/* Variables and functions */
#define  TAS5086_CLK_IDX_MCLK 129 
#define  TAS5086_CLK_IDX_SCLK 128 
 struct tas5086_private* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 

__attribute__((used)) static int tas5086_set_dai_sysclk(struct snd_soc_dai *codec_dai,
				  int clk_id, unsigned int freq, int dir)
{
	struct snd_soc_component *component = codec_dai->component;
	struct tas5086_private *priv = snd_soc_component_get_drvdata(component);

	switch (clk_id) {
	case TAS5086_CLK_IDX_MCLK:
		priv->mclk = freq;
		break;
	case TAS5086_CLK_IDX_SCLK:
		priv->sclk = freq;
		break;
	}

	return 0;
}