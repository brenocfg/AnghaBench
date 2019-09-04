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
struct wm5100_priv {int* out_ena; } ;
struct snd_soc_dapm_widget {int reg; int /*<<< orphan*/  dapm; } ;
struct snd_soc_component {int dummy; } ;
struct snd_kcontrol {int dummy; } ;

/* Variables and functions */
#define  WM5100_CHANNEL_ENABLES_1 129 
#define  WM5100_OUTPUT_ENABLES_2 128 
 struct wm5100_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 struct snd_soc_component* snd_soc_dapm_to_component (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int wm5100_out_ev(struct snd_soc_dapm_widget *w,
			 struct snd_kcontrol *kcontrol,
			 int event)
{
	struct snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	struct wm5100_priv *wm5100 = snd_soc_component_get_drvdata(component);

	switch (w->reg) {
	case WM5100_CHANNEL_ENABLES_1:
		wm5100->out_ena[0] = true;
		break;
	case WM5100_OUTPUT_ENABLES_2:
		wm5100->out_ena[0] = true;
		break;
	default:
		break;
	}

	return 0;
}