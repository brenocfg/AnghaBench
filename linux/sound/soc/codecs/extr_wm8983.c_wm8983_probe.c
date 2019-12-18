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
 int ARRAY_SIZE (int*) ; 
 int WM8983_BIASCUT ; 
 int WM8983_BIAS_CTRL ; 
 int WM8983_DAC_CONTROL ; 
 int WM8983_LOUT1_HP_VOLUME_CTRL ; 
 int WM8983_OUT4_MONO_MIX_CTRL ; 
 int WM8983_SOFTMUTE ; 
 int WM8983_SOFTMUTE_MASK ; 
 int /*<<< orphan*/  WM8983_SOFTWARE_RESET ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int,int,int) ; 
 int snd_soc_component_write (struct snd_soc_component*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int* vol_update_regs ; 

__attribute__((used)) static int wm8983_probe(struct snd_soc_component *component)
{
	int ret;
	int i;

	ret = snd_soc_component_write(component, WM8983_SOFTWARE_RESET, 0);
	if (ret < 0) {
		dev_err(component->dev, "Failed to issue reset: %d\n", ret);
		return ret;
	}

	/* set the vol/gain update bits */
	for (i = 0; i < ARRAY_SIZE(vol_update_regs); ++i)
		snd_soc_component_update_bits(component, vol_update_regs[i],
				    0x100, 0x100);

	/* mute all outputs and set PGAs to minimum gain */
	for (i = WM8983_LOUT1_HP_VOLUME_CTRL;
	     i <= WM8983_OUT4_MONO_MIX_CTRL; ++i)
		snd_soc_component_update_bits(component, i, 0x40, 0x40);

	/* enable soft mute */
	snd_soc_component_update_bits(component, WM8983_DAC_CONTROL,
			    WM8983_SOFTMUTE_MASK,
			    WM8983_SOFTMUTE);

	/* enable BIASCUT */
	snd_soc_component_update_bits(component, WM8983_BIAS_CTRL,
			    WM8983_BIASCUT, WM8983_BIASCUT);
	return 0;
}