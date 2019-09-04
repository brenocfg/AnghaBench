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
struct twl4030_priv {struct twl4030_codec_data* pdata; } ;
struct twl4030_codec_data {scalar_t__ digimic_delay; } ;
struct snd_soc_dapm_widget {int /*<<< orphan*/  dapm; } ;
struct snd_soc_component {int dummy; } ;
struct snd_kcontrol {int dummy; } ;

/* Variables and functions */
 struct twl4030_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 struct snd_soc_component* snd_soc_dapm_to_component (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  twl4030_wait_ms (scalar_t__) ; 

__attribute__((used)) static int digimic_event(struct snd_soc_dapm_widget *w,
			 struct snd_kcontrol *kcontrol, int event)
{
	struct snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	struct twl4030_priv *twl4030 = snd_soc_component_get_drvdata(component);
	struct twl4030_codec_data *pdata = twl4030->pdata;

	if (pdata && pdata->digimic_delay)
		twl4030_wait_ms(pdata->digimic_delay);
	return 0;
}