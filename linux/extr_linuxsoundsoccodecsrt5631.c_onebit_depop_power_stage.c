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

/* Variables and functions */
 int /*<<< orphan*/  RT5631_CP_INTL_REG2 ; 
 int /*<<< orphan*/  RT5631_DEPOP_FUN_CTRL_2 ; 
 unsigned int RT5631_EN_CAP_FREE_DEPOP ; 
 int /*<<< orphan*/  RT5631_EN_ONE_BIT_DEPOP ; 
 int /*<<< orphan*/  RT5631_INT_ST_IRQ_CTRL_2 ; 
 int /*<<< orphan*/  RT5631_SOFT_VOL_CTRL ; 
 int /*<<< orphan*/  RT5631_SPK_INTL_CTRL ; 
 int /*<<< orphan*/  RT5631_TEST_MODE_CTRL ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  rt5631_write_index (struct snd_soc_component*,int /*<<< orphan*/ ,int) ; 
 unsigned int snd_soc_component_read32 (struct snd_soc_component*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_component_write (struct snd_soc_component*,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static void onebit_depop_power_stage(struct snd_soc_component *component, int enable)
{
	unsigned int soft_vol, hp_zc;

	/* enable one-bit depop function */
	snd_soc_component_update_bits(component, RT5631_DEPOP_FUN_CTRL_2,
				RT5631_EN_ONE_BIT_DEPOP, 0);

	/* keep soft volume and zero crossing setting */
	soft_vol = snd_soc_component_read32(component, RT5631_SOFT_VOL_CTRL);
	snd_soc_component_write(component, RT5631_SOFT_VOL_CTRL, 0);
	hp_zc = snd_soc_component_read32(component, RT5631_INT_ST_IRQ_CTRL_2);
	snd_soc_component_write(component, RT5631_INT_ST_IRQ_CTRL_2, hp_zc & 0xf7ff);
	if (enable) {
		/* config one-bit depop parameter */
		rt5631_write_index(component, RT5631_TEST_MODE_CTRL, 0x84c0);
		rt5631_write_index(component, RT5631_SPK_INTL_CTRL, 0x309f);
		rt5631_write_index(component, RT5631_CP_INTL_REG2, 0x6530);
		/* power on capless block */
		snd_soc_component_write(component, RT5631_DEPOP_FUN_CTRL_2,
				RT5631_EN_CAP_FREE_DEPOP);
	} else {
		/* power off capless block */
		snd_soc_component_write(component, RT5631_DEPOP_FUN_CTRL_2, 0);
		msleep(100);
	}

	/* recover soft volume and zero crossing setting */
	snd_soc_component_write(component, RT5631_SOFT_VOL_CTRL, soft_vol);
	snd_soc_component_write(component, RT5631_INT_ST_IRQ_CTRL_2, hp_zc);
}