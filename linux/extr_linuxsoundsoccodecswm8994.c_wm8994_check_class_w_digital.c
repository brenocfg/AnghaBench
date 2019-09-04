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
#define  WM8994_AIF1DAC1L_TO_DAC1L 130 
#define  WM8994_AIF1DAC2L_TO_DAC1L 129 
#define  WM8994_AIF2DACL_TO_DAC1L 128 
 int /*<<< orphan*/  WM8994_CLASS_W_1 ; 
 int /*<<< orphan*/  WM8994_CP_DYN_SRC_SEL_MASK ; 
 int WM8994_CP_DYN_SRC_SEL_SHIFT ; 
 int /*<<< orphan*/  WM8994_DAC1_LEFT_MIXER_ROUTING ; 
 int /*<<< orphan*/  WM8994_DAC1_RIGHT_MIXER_ROUTING ; 
 int /*<<< orphan*/  dev_vdbg (int /*<<< orphan*/ ,char*,...) ; 
 int snd_soc_component_read32 (struct snd_soc_component*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static bool wm8994_check_class_w_digital(struct snd_soc_component *component)
{
	int source = 0;  /* GCC flow analysis can't track enable */
	int reg, reg_r;

	/* We also need the same AIF source for L/R and only one path */
	reg = snd_soc_component_read32(component, WM8994_DAC1_LEFT_MIXER_ROUTING);
	switch (reg) {
	case WM8994_AIF2DACL_TO_DAC1L:
		dev_vdbg(component->dev, "Class W source AIF2DAC\n");
		source = 2 << WM8994_CP_DYN_SRC_SEL_SHIFT;
		break;
	case WM8994_AIF1DAC2L_TO_DAC1L:
		dev_vdbg(component->dev, "Class W source AIF1DAC2\n");
		source = 1 << WM8994_CP_DYN_SRC_SEL_SHIFT;
		break;
	case WM8994_AIF1DAC1L_TO_DAC1L:
		dev_vdbg(component->dev, "Class W source AIF1DAC1\n");
		source = 0 << WM8994_CP_DYN_SRC_SEL_SHIFT;
		break;
	default:
		dev_vdbg(component->dev, "DAC mixer setting: %x\n", reg);
		return false;
	}

	reg_r = snd_soc_component_read32(component, WM8994_DAC1_RIGHT_MIXER_ROUTING);
	if (reg_r != reg) {
		dev_vdbg(component->dev, "Left and right DAC mixers different\n");
		return false;
	}

	/* Set the source up */
	snd_soc_component_update_bits(component, WM8994_CLASS_W_1,
			    WM8994_CP_DYN_SRC_SEL_MASK, source);

	return true;
}