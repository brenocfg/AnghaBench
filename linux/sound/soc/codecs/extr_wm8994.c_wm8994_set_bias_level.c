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
struct wm8994_priv {int /*<<< orphan*/ * cur_fw; struct wm8994* wm8994; } ;
struct wm8994 {int /*<<< orphan*/  type; int /*<<< orphan*/  revision; } ;
struct snd_soc_component {int dummy; } ;
typedef  enum snd_soc_bias_level { ____Placeholder_snd_soc_bias_level } snd_soc_bias_level ;

/* Variables and functions */
#define  SND_SOC_BIAS_OFF 133 
#define  SND_SOC_BIAS_ON 132 
#define  SND_SOC_BIAS_PREPARE 131 
#define  SND_SOC_BIAS_STANDBY 130 
#define  WM1811 129 
#define  WM8958 128 
 int /*<<< orphan*/  WM8958_CHARGE_PUMP_2 ; 
 int WM8958_CP_DISCH ; 
 int WM8958_MICB1_MODE ; 
 int WM8958_MICB2_MODE ; 
 int /*<<< orphan*/  WM8958_MICBIAS1 ; 
 int /*<<< orphan*/  WM8958_MICBIAS2 ; 
 int /*<<< orphan*/  WM8994_ANTIPOP_1 ; 
 int WM8994_LINEOUT1_DISCH ; 
 int WM8994_LINEOUT2_DISCH ; 
 int /*<<< orphan*/  active_dereference (struct snd_soc_component*) ; 
 int /*<<< orphan*/  active_reference (struct snd_soc_component*) ; 
 int const snd_soc_component_get_bias_level (struct snd_soc_component*) ; 
 struct wm8994_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  wm_hubs_set_bias_level (struct snd_soc_component*,int) ; 

__attribute__((used)) static int wm8994_set_bias_level(struct snd_soc_component *component,
				 enum snd_soc_bias_level level)
{
	struct wm8994_priv *wm8994 = snd_soc_component_get_drvdata(component);
	struct wm8994 *control = wm8994->wm8994;

	wm_hubs_set_bias_level(component, level);

	switch (level) {
	case SND_SOC_BIAS_ON:
		break;

	case SND_SOC_BIAS_PREPARE:
		/* MICBIAS into regulating mode */
		switch (control->type) {
		case WM8958:
		case WM1811:
			snd_soc_component_update_bits(component, WM8958_MICBIAS1,
					    WM8958_MICB1_MODE, 0);
			snd_soc_component_update_bits(component, WM8958_MICBIAS2,
					    WM8958_MICB2_MODE, 0);
			break;
		default:
			break;
		}

		if (snd_soc_component_get_bias_level(component) == SND_SOC_BIAS_STANDBY)
			active_reference(component);
		break;

	case SND_SOC_BIAS_STANDBY:
		if (snd_soc_component_get_bias_level(component) == SND_SOC_BIAS_OFF) {
			switch (control->type) {
			case WM8958:
				if (control->revision == 0) {
					/* Optimise performance for rev A */
					snd_soc_component_update_bits(component,
							    WM8958_CHARGE_PUMP_2,
							    WM8958_CP_DISCH,
							    WM8958_CP_DISCH);
				}
				break;

			default:
				break;
			}

			/* Discharge LINEOUT1 & 2 */
			snd_soc_component_update_bits(component, WM8994_ANTIPOP_1,
					    WM8994_LINEOUT1_DISCH |
					    WM8994_LINEOUT2_DISCH,
					    WM8994_LINEOUT1_DISCH |
					    WM8994_LINEOUT2_DISCH);
		}

		if (snd_soc_component_get_bias_level(component) == SND_SOC_BIAS_PREPARE)
			active_dereference(component);

		/* MICBIAS into bypass mode on newer devices */
		switch (control->type) {
		case WM8958:
		case WM1811:
			snd_soc_component_update_bits(component, WM8958_MICBIAS1,
					    WM8958_MICB1_MODE,
					    WM8958_MICB1_MODE);
			snd_soc_component_update_bits(component, WM8958_MICBIAS2,
					    WM8958_MICB2_MODE,
					    WM8958_MICB2_MODE);
			break;
		default:
			break;
		}
		break;

	case SND_SOC_BIAS_OFF:
		if (snd_soc_component_get_bias_level(component) == SND_SOC_BIAS_STANDBY)
			wm8994->cur_fw = NULL;
		break;
	}

	return 0;
}