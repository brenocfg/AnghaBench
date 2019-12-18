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
struct arizona_priv {int out_down_delay; } ;

/* Variables and functions */
 unsigned int ARIZONA_DRE1L_ENA_MASK ; 
 unsigned int ARIZONA_DRE1R_ENA_MASK ; 
 int /*<<< orphan*/  ARIZONA_DRE_ENABLE ; 
#define  ARIZONA_OUT1L_ENA_SHIFT 129 
#define  ARIZONA_OUT1R_ENA_SHIFT 128 
 int /*<<< orphan*/  ARIZONA_SPARE_TRIGGERS ; 
 int /*<<< orphan*/  ARIZONA_WS_TRG1 ; 
 int /*<<< orphan*/  ARIZONA_WS_TRG2 ; 
 struct arizona_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 unsigned int snd_soc_component_read32 (struct snd_soc_component*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct snd_soc_component* snd_soc_dapm_to_component (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int wm5110_hp_pre_disable(struct snd_soc_dapm_widget *w)
{
	struct snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	struct arizona_priv *priv = snd_soc_component_get_drvdata(component);
	unsigned int val = snd_soc_component_read32(component, ARIZONA_DRE_ENABLE);

	switch (w->shift) {
	case ARIZONA_OUT1L_ENA_SHIFT:
		if (!(val & ARIZONA_DRE1L_ENA_MASK)) {
			snd_soc_component_update_bits(component,
						      ARIZONA_SPARE_TRIGGERS,
						      ARIZONA_WS_TRG1,
						      ARIZONA_WS_TRG1);
			snd_soc_component_update_bits(component,
						      ARIZONA_SPARE_TRIGGERS,
						      ARIZONA_WS_TRG1, 0);
			priv->out_down_delay += 27;
		}
		break;
	case ARIZONA_OUT1R_ENA_SHIFT:
		if (!(val & ARIZONA_DRE1R_ENA_MASK)) {
			snd_soc_component_update_bits(component,
						      ARIZONA_SPARE_TRIGGERS,
						      ARIZONA_WS_TRG2,
						      ARIZONA_WS_TRG2);
			snd_soc_component_update_bits(component,
						      ARIZONA_SPARE_TRIGGERS,
						      ARIZONA_WS_TRG2, 0);
			priv->out_down_delay += 27;
		}
		break;
	default:
		break;
	}

	return 0;
}