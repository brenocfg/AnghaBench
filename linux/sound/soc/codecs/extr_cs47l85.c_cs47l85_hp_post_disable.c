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
struct snd_soc_component {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  MADERA_DCS_HP1L_CONTROL ; 
 int /*<<< orphan*/  MADERA_DCS_HP1R_CONTROL ; 
 int /*<<< orphan*/  MADERA_EDRE_HP_STEREO_CONTROL ; 
#define  MADERA_OUT1L_ENA_SHIFT 129 
#define  MADERA_OUT1R_ENA_SHIFT 128 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_component_write (struct snd_soc_component*,int /*<<< orphan*/ ,int) ; 
 struct snd_soc_component* snd_soc_dapm_to_component (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cs47l85_hp_post_disable(struct snd_soc_dapm_widget *w)
{
	struct snd_soc_component *component =
		snd_soc_dapm_to_component(w->dapm);

	switch (w->shift) {
	case MADERA_OUT1L_ENA_SHIFT:
		snd_soc_component_write(component, MADERA_DCS_HP1L_CONTROL,
					0x2006);
		break;
	case MADERA_OUT1R_ENA_SHIFT:
		snd_soc_component_write(component, MADERA_DCS_HP1R_CONTROL,
					0x2006);
		break;
	default:
		return;
	}

	/* Only get to here for OUT1L and OUT1R */
	snd_soc_component_update_bits(component,
				      MADERA_EDRE_HP_STEREO_CONTROL,
				      0x0001, 0);
}