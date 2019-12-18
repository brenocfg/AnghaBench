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
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 int snd_soc_add_component_controls (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int snd_soc_add_dai_controls (struct snd_soc_dai*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stm32_spdifrx_ctrls ; 
 int /*<<< orphan*/  stm32_spdifrx_iec_ctrls ; 

__attribute__((used)) static int stm32_spdifrx_dai_register_ctrls(struct snd_soc_dai *cpu_dai)
{
	int ret;

	ret = snd_soc_add_dai_controls(cpu_dai, stm32_spdifrx_iec_ctrls,
				       ARRAY_SIZE(stm32_spdifrx_iec_ctrls));
	if (ret < 0)
		return ret;

	return snd_soc_add_component_controls(cpu_dai->component,
					      stm32_spdifrx_ctrls,
					      ARRAY_SIZE(stm32_spdifrx_ctrls));
}