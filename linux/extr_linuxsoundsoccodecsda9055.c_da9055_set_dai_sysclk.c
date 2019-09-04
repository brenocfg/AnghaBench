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
struct snd_soc_dai {int /*<<< orphan*/  dev; struct snd_soc_component* component; } ;
struct snd_soc_component {int dummy; } ;
struct da9055_priv {unsigned int mclk_rate; } ;

/* Variables and functions */
#define  DA9055_CLKSRC_MCLK 128 
 int EINVAL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 struct da9055_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 

__attribute__((used)) static int da9055_set_dai_sysclk(struct snd_soc_dai *codec_dai,
				 int clk_id, unsigned int freq, int dir)
{
	struct snd_soc_component *component = codec_dai->component;
	struct da9055_priv *da9055 = snd_soc_component_get_drvdata(component);

	switch (clk_id) {
	case DA9055_CLKSRC_MCLK:
		switch (freq) {
		case 11289600:
		case 12000000:
		case 12288000:
		case 13000000:
		case 13500000:
		case 14400000:
		case 19200000:
		case 19680000:
		case 19800000:
			da9055->mclk_rate = freq;
			return 0;
		default:
			dev_err(codec_dai->dev, "Unsupported MCLK value %d\n",
				freq);
			return -EINVAL;
		}
		break;
	default:
		dev_err(codec_dai->dev, "Unknown clock source %d\n", clk_id);
		return -EINVAL;
	}
}