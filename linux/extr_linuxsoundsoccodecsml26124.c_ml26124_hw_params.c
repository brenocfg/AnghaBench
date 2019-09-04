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
struct snd_soc_component {int /*<<< orphan*/  dev; } ;
struct snd_pcm_substream {int dummy; } ;
struct snd_pcm_hw_params {int dummy; } ;
struct ml26124_priv {int mclk; int rate; scalar_t__ clk_in; struct snd_pcm_substream* substream; } ;
struct TYPE_2__ {int pllnl; int pllnh; int pllml; int pllmh; int plldiv; } ;

/* Variables and functions */
 int BIT (int) ; 
 int /*<<< orphan*/  ML26124_CLK_CTL ; 
 int /*<<< orphan*/  ML26124_PLLDIV ; 
 int /*<<< orphan*/  ML26124_PLLMH ; 
 int /*<<< orphan*/  ML26124_PLLML ; 
 int /*<<< orphan*/  ML26124_PLLNH ; 
 int /*<<< orphan*/  ML26124_PLLNL ; 
 int /*<<< orphan*/  ML26124_SMPLING_RATE ; 
 TYPE_1__* coeff_div ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int get_coeff (int,int) ; 
 int get_srate (int) ; 
 int params_rate (struct snd_pcm_hw_params*) ; 
 struct ml26124_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int ml26124_hw_params(struct snd_pcm_substream *substream,
			    struct snd_pcm_hw_params *hw_params,
			    struct snd_soc_dai *dai)
{
	struct snd_soc_component *component = dai->component;
	struct ml26124_priv *priv = snd_soc_component_get_drvdata(component);
	int i = get_coeff(priv->mclk, params_rate(hw_params));
	int srate;

	if (i < 0)
		return i;
	priv->substream = substream;
	priv->rate = params_rate(hw_params);

	if (priv->clk_in) {
		switch (priv->mclk / params_rate(hw_params)) {
		case 256:
			snd_soc_component_update_bits(component, ML26124_CLK_CTL,
					    BIT(0) | BIT(1), 1);
			break;
		case 512:
			snd_soc_component_update_bits(component, ML26124_CLK_CTL,
					    BIT(0) | BIT(1), 2);
			break;
		case 1024:
			snd_soc_component_update_bits(component, ML26124_CLK_CTL,
					    BIT(0) | BIT(1), 3);
			break;
		default:
			dev_err(component->dev, "Unsupported MCLKI\n");
			break;
		}
	} else {
		snd_soc_component_update_bits(component, ML26124_CLK_CTL,
				    BIT(0) | BIT(1), 0);
	}

	srate = get_srate(params_rate(hw_params));
	if (srate < 0)
		return srate;

	snd_soc_component_update_bits(component, ML26124_SMPLING_RATE, 0xf, srate);
	snd_soc_component_update_bits(component, ML26124_PLLNL, 0xff, coeff_div[i].pllnl);
	snd_soc_component_update_bits(component, ML26124_PLLNH, 0x1, coeff_div[i].pllnh);
	snd_soc_component_update_bits(component, ML26124_PLLML, 0xff, coeff_div[i].pllml);
	snd_soc_component_update_bits(component, ML26124_PLLMH, 0x3f, coeff_div[i].pllmh);
	snd_soc_component_update_bits(component, ML26124_PLLDIV, 0x1f, coeff_div[i].plldiv);

	return 0;
}