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

/* Variables and functions */
 int /*<<< orphan*/  CS4341_REG_VOLA ; 
 int /*<<< orphan*/  CS4341_REG_VOLB ; 
 int /*<<< orphan*/  CS4341_VOLX_MUTE ; 
 int snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int cs4341_digital_mute(struct snd_soc_dai *dai, int mute)
{
	struct snd_soc_component *component = dai->component;
	int ret;

	ret = snd_soc_component_update_bits(component, CS4341_REG_VOLA,
					    CS4341_VOLX_MUTE,
					    mute ? CS4341_VOLX_MUTE : 0);
	if (ret < 0)
		return ret;

	return snd_soc_component_update_bits(component, CS4341_REG_VOLB,
					     CS4341_VOLX_MUTE,
					     mute ? CS4341_VOLX_MUTE : 0);
}