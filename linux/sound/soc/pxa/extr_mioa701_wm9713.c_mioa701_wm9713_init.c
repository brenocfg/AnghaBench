#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct snd_soc_pcm_runtime {TYPE_1__* codec_dai; } ;
struct snd_soc_component {int dummy; } ;
struct TYPE_2__ {struct snd_soc_component* component; } ;

/* Variables and functions */
 int /*<<< orphan*/  AC97_3D_CONTROL ; 
 int /*<<< orphan*/  AC97_GPIO_CFG ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int,int) ; 

__attribute__((used)) static int mioa701_wm9713_init(struct snd_soc_pcm_runtime *rtd)
{
	struct snd_soc_component *component = rtd->codec_dai->component;

	/* Prepare GPIO8 for rear speaker amplifier */
	snd_soc_component_update_bits(component, AC97_GPIO_CFG, 0x100, 0x100);

	/* Prepare MIC input */
	snd_soc_component_update_bits(component, AC97_3D_CONTROL, 0xc000, 0xc000);

	return 0;
}