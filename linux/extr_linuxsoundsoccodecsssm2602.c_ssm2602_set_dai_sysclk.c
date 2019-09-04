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
struct ssm2602_priv {unsigned int sysclk; unsigned int clk_out_pwr; int /*<<< orphan*/  regmap; int /*<<< orphan*/ * sysclk_constraints; } ;
struct snd_soc_dai {struct snd_soc_component* component; } ;
struct snd_soc_component {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 unsigned int PWR_CLK_OUT_PDN ; 
 unsigned int PWR_OSC_PDN ; 
 int SND_SOC_CLOCK_IN ; 
#define  SSM2602_CLK_CLKOUT 129 
#define  SSM2602_CLK_XTO 128 
 int /*<<< orphan*/  SSM2602_PWR ; 
 int SSM2602_SYSCLK ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,unsigned int) ; 
 struct ssm2602_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int /*<<< orphan*/  ssm2602_constraints_11289600 ; 
 int /*<<< orphan*/  ssm2602_constraints_12288000 ; 

__attribute__((used)) static int ssm2602_set_dai_sysclk(struct snd_soc_dai *codec_dai,
		int clk_id, unsigned int freq, int dir)
{
	struct snd_soc_component *component = codec_dai->component;
	struct ssm2602_priv *ssm2602 = snd_soc_component_get_drvdata(component);

	if (dir == SND_SOC_CLOCK_IN) {
		if (clk_id != SSM2602_SYSCLK)
			return -EINVAL;

		switch (freq) {
		case 12288000:
		case 18432000:
			ssm2602->sysclk_constraints = &ssm2602_constraints_12288000;
			break;
		case 11289600:
		case 16934400:
			ssm2602->sysclk_constraints = &ssm2602_constraints_11289600;
			break;
		case 12000000:
			ssm2602->sysclk_constraints = NULL;
			break;
		default:
			return -EINVAL;
		}
		ssm2602->sysclk = freq;
	} else {
		unsigned int mask;

		switch (clk_id) {
		case SSM2602_CLK_CLKOUT:
			mask = PWR_CLK_OUT_PDN;
			break;
		case SSM2602_CLK_XTO:
			mask = PWR_OSC_PDN;
			break;
		default:
			return -EINVAL;
		}

		if (freq == 0)
			ssm2602->clk_out_pwr |= mask;
		else
			ssm2602->clk_out_pwr &= ~mask;

		regmap_update_bits(ssm2602->regmap, SSM2602_PWR,
			PWR_CLK_OUT_PDN | PWR_OSC_PDN, ssm2602->clk_out_pwr);
	}

	return 0;
}