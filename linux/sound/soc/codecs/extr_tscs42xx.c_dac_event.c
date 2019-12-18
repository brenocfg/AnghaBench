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
struct tscs42xx {int coeff_ram_synced; int /*<<< orphan*/  coeff_ram_lock; int /*<<< orphan*/  coeff_ram; } ;
struct snd_soc_dapm_widget {int /*<<< orphan*/  dapm; } ;
struct snd_soc_component {int dummy; } ;
struct snd_kcontrol {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  COEFF_RAM_COEFF_COUNT ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct tscs42xx* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 struct snd_soc_component* snd_soc_dapm_to_component (int /*<<< orphan*/ ) ; 
 int write_coeff_ram (struct snd_soc_component*,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dac_event(struct snd_soc_dapm_widget *w,
		     struct snd_kcontrol *kcontrol, int event)
{
	struct snd_soc_component *component =
		snd_soc_dapm_to_component(w->dapm);
	struct tscs42xx *tscs42xx = snd_soc_component_get_drvdata(component);
	int ret;

	mutex_lock(&tscs42xx->coeff_ram_lock);

	if (!tscs42xx->coeff_ram_synced) {
		ret = write_coeff_ram(component, tscs42xx->coeff_ram, 0x00,
			COEFF_RAM_COEFF_COUNT);
		if (ret < 0)
			goto exit;
		tscs42xx->coeff_ram_synced = true;
	}

	ret = 0;
exit:
	mutex_unlock(&tscs42xx->coeff_ram_lock);

	return ret;
}