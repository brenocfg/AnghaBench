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
typedef  int u16 ;
struct snd_soc_dai {struct snd_soc_component* component; } ;
struct snd_soc_component {int dummy; } ;
struct snd_pcm_substream {int dummy; } ;
struct snd_pcm_hw_params {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  LM49453_P0_ADC_CLK_DIV_REG ; 
 int /*<<< orphan*/  LM49453_P0_DAC_HP_CLK_DIV_REG ; 
 int params_rate (struct snd_pcm_hw_params*) ; 
 int /*<<< orphan*/  snd_soc_component_write (struct snd_soc_component*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int lm49453_hw_params(struct snd_pcm_substream *substream,
			     struct snd_pcm_hw_params *params,
			     struct snd_soc_dai *dai)
{
	struct snd_soc_component *component = dai->component;
	u16 clk_div = 0;

	/* Setting DAC clock dividers based on substream sample rate. */
	switch (params_rate(params)) {
	case 8000:
	case 16000:
	case 32000:
	case 24000:
	case 48000:
		clk_div = 256;
		break;
	case 11025:
	case 22050:
	case 44100:
		clk_div = 216;
		break;
	case 96000:
		clk_div = 127;
		break;
	default:
		return -EINVAL;
	}

	snd_soc_component_write(component, LM49453_P0_ADC_CLK_DIV_REG, clk_div);
	snd_soc_component_write(component, LM49453_P0_DAC_HP_CLK_DIV_REG, clk_div);

	return 0;
}