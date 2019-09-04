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
 int /*<<< orphan*/  RT5631_DEPOP_FUN_CTRL_1 ; 
 int /*<<< orphan*/  RT5631_DEPOP_FUN_CTRL_2 ; 
 unsigned int RT5631_EN_HP_L_M_UN_MUTE_DEPOP ; 
 unsigned int RT5631_EN_HP_R_M_UN_MUTE_DEPOP ; 
 unsigned int RT5631_EN_MUTE_UNMUTE_DEPOP ; 
 int RT5631_EN_ONE_BIT_DEPOP ; 
 int /*<<< orphan*/  RT5631_HP_OUT_VOL ; 
 int /*<<< orphan*/  RT5631_INT_ST_IRQ_CTRL_2 ; 
 int RT5631_L_MUTE ; 
 unsigned int RT5631_POW_ON_SOFT_GEN ; 
 int RT5631_R_MUTE ; 
 int /*<<< orphan*/  RT5631_SOFT_VOL_CTRL ; 
 int /*<<< orphan*/  RT5631_SPK_INTL_CTRL ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  rt5631_write_index (struct snd_soc_component*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  schedule_timeout_uninterruptible (int /*<<< orphan*/ ) ; 
 unsigned int snd_soc_component_read32 (struct snd_soc_component*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  snd_soc_component_write (struct snd_soc_component*,int /*<<< orphan*/ ,unsigned int) ; 

__attribute__((used)) static void depop_seq_mute_stage(struct snd_soc_component *component, int enable)
{
	unsigned int soft_vol, hp_zc;

	/* depop control by register */
	snd_soc_component_update_bits(component, RT5631_DEPOP_FUN_CTRL_2,
		RT5631_EN_ONE_BIT_DEPOP, RT5631_EN_ONE_BIT_DEPOP);

	/* keep soft volume and zero crossing setting */
	soft_vol = snd_soc_component_read32(component, RT5631_SOFT_VOL_CTRL);
	snd_soc_component_write(component, RT5631_SOFT_VOL_CTRL, 0);
	hp_zc = snd_soc_component_read32(component, RT5631_INT_ST_IRQ_CTRL_2);
	snd_soc_component_write(component, RT5631_INT_ST_IRQ_CTRL_2, hp_zc & 0xf7ff);
	if (enable) {
		schedule_timeout_uninterruptible(msecs_to_jiffies(10));

		/* config depop sequence parameter */
		rt5631_write_index(component, RT5631_SPK_INTL_CTRL, 0x302f);
		snd_soc_component_write(component, RT5631_DEPOP_FUN_CTRL_1,
			RT5631_POW_ON_SOFT_GEN | RT5631_EN_MUTE_UNMUTE_DEPOP |
			RT5631_EN_HP_R_M_UN_MUTE_DEPOP |
			RT5631_EN_HP_L_M_UN_MUTE_DEPOP);

		snd_soc_component_update_bits(component, RT5631_HP_OUT_VOL,
				RT5631_L_MUTE | RT5631_R_MUTE, 0);
		msleep(160);
	} else {
		/* config depop sequence parameter */
		rt5631_write_index(component, RT5631_SPK_INTL_CTRL, 0x302f);
		snd_soc_component_write(component, RT5631_DEPOP_FUN_CTRL_1,
			RT5631_POW_ON_SOFT_GEN | RT5631_EN_MUTE_UNMUTE_DEPOP |
			RT5631_EN_HP_R_M_UN_MUTE_DEPOP |
			RT5631_EN_HP_L_M_UN_MUTE_DEPOP);

		snd_soc_component_update_bits(component, RT5631_HP_OUT_VOL,
			RT5631_L_MUTE | RT5631_R_MUTE,
			RT5631_L_MUTE | RT5631_R_MUTE);
		msleep(150);
	}

	/* recover soft volume and zero crossing setting */
	snd_soc_component_write(component, RT5631_SOFT_VOL_CTRL, soft_vol);
	snd_soc_component_write(component, RT5631_INT_ST_IRQ_CTRL_2, hp_zc);
}