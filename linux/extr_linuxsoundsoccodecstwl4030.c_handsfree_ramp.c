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
 unsigned char TWL4030_HF_CTL_HB_EN ; 
 unsigned char TWL4030_HF_CTL_LOOP_EN ; 
 unsigned char TWL4030_HF_CTL_RAMP_EN ; 
 unsigned char TWL4030_HF_CTL_REF_EN ; 
 unsigned char twl4030_read (struct snd_soc_component*,int) ; 
 int /*<<< orphan*/  twl4030_write (struct snd_soc_component*,int,unsigned char) ; 
 int /*<<< orphan*/  udelay (int) ; 

__attribute__((used)) static void handsfree_ramp(struct snd_soc_component *component, int reg, int ramp)
{
	unsigned char hs_ctl;

	hs_ctl = twl4030_read(component, reg);

	if (ramp) {
		/* HF ramp-up */
		hs_ctl |= TWL4030_HF_CTL_REF_EN;
		twl4030_write(component, reg, hs_ctl);
		udelay(10);
		hs_ctl |= TWL4030_HF_CTL_RAMP_EN;
		twl4030_write(component, reg, hs_ctl);
		udelay(40);
		hs_ctl |= TWL4030_HF_CTL_LOOP_EN;
		hs_ctl |= TWL4030_HF_CTL_HB_EN;
		twl4030_write(component, reg, hs_ctl);
	} else {
		/* HF ramp-down */
		hs_ctl &= ~TWL4030_HF_CTL_LOOP_EN;
		hs_ctl &= ~TWL4030_HF_CTL_HB_EN;
		twl4030_write(component, reg, hs_ctl);
		hs_ctl &= ~TWL4030_HF_CTL_RAMP_EN;
		twl4030_write(component, reg, hs_ctl);
		udelay(40);
		hs_ctl &= ~TWL4030_HF_CTL_REF_EN;
		twl4030_write(component, reg, hs_ctl);
	}
}