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
struct snd_soc_component {int dummy; } ;
struct adau1701 {unsigned int sysclk; int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
#define  ADAU1701_CLK_SRC_MCLK 129 
#define  ADAU1701_CLK_SRC_OSC 128 
 int /*<<< orphan*/  ADAU1701_OSCIPOW ; 
 unsigned int ADAU1701_OSCIPOW_OPD ; 
 int EINVAL ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int,unsigned int) ; 
 struct adau1701* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 

__attribute__((used)) static int adau1701_set_sysclk(struct snd_soc_component *component, int clk_id,
	int source, unsigned int freq, int dir)
{
	unsigned int val;
	struct adau1701 *adau1701 = snd_soc_component_get_drvdata(component);

	switch (clk_id) {
	case ADAU1701_CLK_SRC_OSC:
		val = 0x0;
		break;
	case ADAU1701_CLK_SRC_MCLK:
		val = ADAU1701_OSCIPOW_OPD;
		break;
	default:
		return -EINVAL;
	}

	regmap_update_bits(adau1701->regmap, ADAU1701_OSCIPOW,
			   ADAU1701_OSCIPOW_OPD, val);
	adau1701->sysclk = freq;

	return 0;
}