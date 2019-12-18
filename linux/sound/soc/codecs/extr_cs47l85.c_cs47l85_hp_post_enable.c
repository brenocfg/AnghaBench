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
struct snd_soc_dapm_widget {int shift; int /*<<< orphan*/  dapm; } ;
struct snd_soc_component {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  MADERA_EDRE_HP_STEREO_CONTROL ; 
 unsigned int MADERA_OUT1L_ENA ; 
#define  MADERA_OUT1L_ENA_SHIFT 129 
 unsigned int MADERA_OUT1R_ENA ; 
#define  MADERA_OUT1R_ENA_SHIFT 128 
 int /*<<< orphan*/  MADERA_OUTPUT_ENABLES_1 ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int snd_soc_component_read (struct snd_soc_component*,int /*<<< orphan*/ ,unsigned int*) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int,int) ; 
 struct snd_soc_component* snd_soc_dapm_to_component (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cs47l85_hp_post_enable(struct snd_soc_dapm_widget *w)
{
	struct snd_soc_component *component =
		snd_soc_dapm_to_component(w->dapm);
	unsigned int val;
	int ret;

	switch (w->shift) {
	case MADERA_OUT1L_ENA_SHIFT:
	case MADERA_OUT1R_ENA_SHIFT:
		ret = snd_soc_component_read(component, MADERA_OUTPUT_ENABLES_1,
					     &val);
		if (ret) {
			dev_err(component->dev,
				"Failed to check output enables: %d\n", ret);
			return;
		}

		val &= (MADERA_OUT1L_ENA | MADERA_OUT1R_ENA);

		if (val != (MADERA_OUT1L_ENA | MADERA_OUT1R_ENA))
			break;

		snd_soc_component_update_bits(component,
					      MADERA_EDRE_HP_STEREO_CONTROL,
					      0x0001, 1);
		break;
	default:
		break;
	}
}