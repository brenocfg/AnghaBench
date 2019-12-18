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
struct snd_soc_dai {int /*<<< orphan*/  component; } ;

/* Variables and functions */
 int BIT (int) ; 
 int /*<<< orphan*/  LM49453_P0_DAC_DSP_REG ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int lm49453_ha_mute(struct snd_soc_dai *dai, int mute)
{
	snd_soc_component_update_bits(dai->component, LM49453_P0_DAC_DSP_REG, BIT(7)|BIT(6),
			    (mute ? (BIT(7)|BIT(6)) : 0));
	return 0;
}