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
struct wm0010_priv {int /*<<< orphan*/  lock; } ;
struct snd_soc_component {int dummy; } ;
typedef  enum snd_soc_bias_level { ____Placeholder_snd_soc_bias_level } snd_soc_bias_level ;

/* Variables and functions */
#define  SND_SOC_BIAS_OFF 131 
#define  SND_SOC_BIAS_ON 130 
#define  SND_SOC_BIAS_PREPARE 129 
#define  SND_SOC_BIAS_STANDBY 128 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int const snd_soc_component_get_bias_level (struct snd_soc_component*) ; 
 struct wm0010_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int /*<<< orphan*/  wm0010_boot (struct snd_soc_component*) ; 
 int /*<<< orphan*/  wm0010_halt (struct snd_soc_component*) ; 

__attribute__((used)) static int wm0010_set_bias_level(struct snd_soc_component *component,
				 enum snd_soc_bias_level level)
{
	struct wm0010_priv *wm0010 = snd_soc_component_get_drvdata(component);

	switch (level) {
	case SND_SOC_BIAS_ON:
		if (snd_soc_component_get_bias_level(component) == SND_SOC_BIAS_PREPARE)
			wm0010_boot(component);
		break;
	case SND_SOC_BIAS_PREPARE:
		break;
	case SND_SOC_BIAS_STANDBY:
		if (snd_soc_component_get_bias_level(component) == SND_SOC_BIAS_PREPARE) {
			mutex_lock(&wm0010->lock);
			wm0010_halt(component);
			mutex_unlock(&wm0010->lock);
		}
		break;
	case SND_SOC_BIAS_OFF:
		break;
	}

	return 0;
}