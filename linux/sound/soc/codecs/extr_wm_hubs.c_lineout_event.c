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
struct wm_hubs_data {int lineout1n_ena; int lineout1p_ena; int lineout2n_ena; int lineout2p_ena; } ;
struct snd_soc_dapm_widget {int shift; int /*<<< orphan*/  dapm; } ;
struct snd_soc_component {int dummy; } ;
struct snd_kcontrol {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 int SND_SOC_DAPM_EVENT_ON (int) ; 
 int /*<<< orphan*/  WARN (int,char*) ; 
#define  WM8993_LINEOUT1N_ENA_SHIFT 131 
#define  WM8993_LINEOUT1P_ENA_SHIFT 130 
#define  WM8993_LINEOUT2N_ENA_SHIFT 129 
#define  WM8993_LINEOUT2P_ENA_SHIFT 128 
 struct wm_hubs_data* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 struct snd_soc_component* snd_soc_dapm_to_component (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int lineout_event(struct snd_soc_dapm_widget *w,
			 struct snd_kcontrol *control, int event)
{
	struct snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	struct wm_hubs_data *hubs = snd_soc_component_get_drvdata(component);
	bool *flag;

	switch (w->shift) {
	case WM8993_LINEOUT1N_ENA_SHIFT:
		flag = &hubs->lineout1n_ena;
		break;
	case WM8993_LINEOUT1P_ENA_SHIFT:
		flag = &hubs->lineout1p_ena;
		break;
	case WM8993_LINEOUT2N_ENA_SHIFT:
		flag = &hubs->lineout2n_ena;
		break;
	case WM8993_LINEOUT2P_ENA_SHIFT:
		flag = &hubs->lineout2p_ena;
		break;
	default:
		WARN(1, "Unknown line output");
		return -EINVAL;
	}

	*flag = SND_SOC_DAPM_EVENT_ON(event);

	return 0;
}