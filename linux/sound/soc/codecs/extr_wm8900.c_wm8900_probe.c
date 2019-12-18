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
struct snd_soc_component {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int ENODEV ; 
 int /*<<< orphan*/  SND_SOC_BIAS_STANDBY ; 
 int /*<<< orphan*/  WM8900_REG_ID ; 
 int /*<<< orphan*/  WM8900_REG_LADC_DV ; 
 int /*<<< orphan*/  WM8900_REG_LDAC_DV ; 
 int /*<<< orphan*/  WM8900_REG_LINVOL ; 
 int /*<<< orphan*/  WM8900_REG_LOUT1CTL ; 
 int /*<<< orphan*/  WM8900_REG_LOUT2CTL ; 
 int /*<<< orphan*/  WM8900_REG_OUTBIASCTL ; 
 int /*<<< orphan*/  WM8900_REG_RADC_DV ; 
 int /*<<< orphan*/  WM8900_REG_RDAC_DV ; 
 int /*<<< orphan*/  WM8900_REG_RINVOL ; 
 int /*<<< orphan*/  WM8900_REG_ROUT1CTL ; 
 int /*<<< orphan*/  WM8900_REG_ROUT2CTL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  snd_soc_component_force_bias_level (struct snd_soc_component*,int /*<<< orphan*/ ) ; 
 int snd_soc_component_read32 (struct snd_soc_component*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  snd_soc_component_write (struct snd_soc_component*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  wm8900_reset (struct snd_soc_component*) ; 

__attribute__((used)) static int wm8900_probe(struct snd_soc_component *component)
{
	int reg;

	reg = snd_soc_component_read32(component, WM8900_REG_ID);
	if (reg != 0x8900) {
		dev_err(component->dev, "Device is not a WM8900 - ID %x\n", reg);
		return -ENODEV;
	}

	wm8900_reset(component);

	/* Turn the chip on */
	snd_soc_component_force_bias_level(component, SND_SOC_BIAS_STANDBY);

	/* Latch the volume update bits */
	snd_soc_component_update_bits(component, WM8900_REG_LINVOL, 0x100, 0x100);
	snd_soc_component_update_bits(component, WM8900_REG_RINVOL, 0x100, 0x100);
	snd_soc_component_update_bits(component, WM8900_REG_LOUT1CTL, 0x100, 0x100);
	snd_soc_component_update_bits(component, WM8900_REG_ROUT1CTL, 0x100, 0x100);
	snd_soc_component_update_bits(component, WM8900_REG_LOUT2CTL, 0x100, 0x100);
	snd_soc_component_update_bits(component, WM8900_REG_ROUT2CTL, 0x100, 0x100);
	snd_soc_component_update_bits(component, WM8900_REG_LDAC_DV, 0x100, 0x100);
	snd_soc_component_update_bits(component, WM8900_REG_RDAC_DV, 0x100, 0x100);
	snd_soc_component_update_bits(component, WM8900_REG_LADC_DV, 0x100, 0x100);
	snd_soc_component_update_bits(component, WM8900_REG_RADC_DV, 0x100, 0x100);

	/* Set the DAC and mixer output bias */
	snd_soc_component_write(component, WM8900_REG_OUTBIASCTL, 0x81);

	return 0;
}