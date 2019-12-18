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
struct snd_soc_component {int /*<<< orphan*/  dev; } ;
struct max98090_priv {unsigned int sysclk; unsigned int pclk; int /*<<< orphan*/  mclk; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  IS_ERR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  M98090_PSCLK_DIV1 ; 
 int /*<<< orphan*/  M98090_PSCLK_DIV2 ; 
 int /*<<< orphan*/  M98090_PSCLK_DIV4 ; 
 int /*<<< orphan*/  M98090_REG_SYSTEM_CLOCK ; 
 unsigned int clk_round_rate (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  clk_set_rate (int /*<<< orphan*/ ,unsigned int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 struct max98090_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int /*<<< orphan*/  snd_soc_component_write (struct snd_soc_component*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int max98090_dai_set_sysclk(struct snd_soc_dai *dai,
				   int clk_id, unsigned int freq, int dir)
{
	struct snd_soc_component *component = dai->component;
	struct max98090_priv *max98090 = snd_soc_component_get_drvdata(component);

	/* Requested clock frequency is already setup */
	if (freq == max98090->sysclk)
		return 0;

	if (!IS_ERR(max98090->mclk)) {
		freq = clk_round_rate(max98090->mclk, freq);
		clk_set_rate(max98090->mclk, freq);
	}

	/* Setup clocks for slave mode, and using the PLL
	 * PSCLK = 0x01 (when master clk is 10MHz to 20MHz)
	 *		 0x02 (when master clk is 20MHz to 40MHz)..
	 *		 0x03 (when master clk is 40MHz to 60MHz)..
	 */
	if ((freq >= 10000000) && (freq <= 20000000)) {
		snd_soc_component_write(component, M98090_REG_SYSTEM_CLOCK,
			M98090_PSCLK_DIV1);
		max98090->pclk = freq;
	} else if ((freq > 20000000) && (freq <= 40000000)) {
		snd_soc_component_write(component, M98090_REG_SYSTEM_CLOCK,
			M98090_PSCLK_DIV2);
		max98090->pclk = freq >> 1;
	} else if ((freq > 40000000) && (freq <= 60000000)) {
		snd_soc_component_write(component, M98090_REG_SYSTEM_CLOCK,
			M98090_PSCLK_DIV4);
		max98090->pclk = freq >> 2;
	} else {
		dev_err(component->dev, "Invalid master clock frequency\n");
		return -EINVAL;
	}

	max98090->sysclk = freq;

	return 0;
}