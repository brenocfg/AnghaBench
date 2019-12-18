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
 int M98095_00F_HOST_CFG ; 
 int M98095_010_HOST_INT_CFG ; 
 int M98095_097_PWR_SYS ; 
 int M98095_REG_MAX_CACHED ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  snd_soc_component_read32 (struct snd_soc_component*,int) ; 
 int snd_soc_component_write (struct snd_soc_component*,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int max98095_reset(struct snd_soc_component *component)
{
	int i, ret;

	/* Gracefully reset the DSP core and the codec hardware
	 * in a proper sequence */
	ret = snd_soc_component_write(component, M98095_00F_HOST_CFG, 0);
	if (ret < 0) {
		dev_err(component->dev, "Failed to reset DSP: %d\n", ret);
		return ret;
	}

	ret = snd_soc_component_write(component, M98095_097_PWR_SYS, 0);
	if (ret < 0) {
		dev_err(component->dev, "Failed to reset component: %d\n", ret);
		return ret;
	}

	/* Reset to hardware default for registers, as there is not
	 * a soft reset hardware control register */
	for (i = M98095_010_HOST_INT_CFG; i < M98095_REG_MAX_CACHED; i++) {
		ret = snd_soc_component_write(component, i, snd_soc_component_read32(component, i));
		if (ret < 0) {
			dev_err(component->dev, "Failed to reset: %d\n", ret);
			return ret;
		}
	}

	return ret;
}