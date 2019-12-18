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
struct snd_soc_dai {struct snd_soc_component* component; } ;
struct snd_soc_component {int dummy; } ;
struct es8328_priv {int mclkdiv2; int /*<<< orphan*/ * mclk_ratios; int /*<<< orphan*/ * sysclk_constraints; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  constraints_11289 ; 
 int /*<<< orphan*/  constraints_12288 ; 
 int /*<<< orphan*/ * ratios_11289 ; 
 int /*<<< orphan*/ * ratios_12288 ; 
 struct es8328_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 

__attribute__((used)) static int es8328_set_sysclk(struct snd_soc_dai *codec_dai,
		int clk_id, unsigned int freq, int dir)
{
	struct snd_soc_component *component = codec_dai->component;
	struct es8328_priv *es8328 = snd_soc_component_get_drvdata(component);
	int mclkdiv2 = 0;

	switch (freq) {
	case 0:
		es8328->sysclk_constraints = NULL;
		es8328->mclk_ratios = NULL;
		break;
	case 22579200:
		mclkdiv2 = 1;
		/* fall through */
	case 11289600:
		es8328->sysclk_constraints = &constraints_11289;
		es8328->mclk_ratios = ratios_11289;
		break;
	case 24576000:
		mclkdiv2 = 1;
		/* fall through */
	case 12288000:
		es8328->sysclk_constraints = &constraints_12288;
		es8328->mclk_ratios = ratios_12288;
		break;
	default:
		return -EINVAL;
	}

	es8328->mclkdiv2 = mclkdiv2;
	return 0;
}