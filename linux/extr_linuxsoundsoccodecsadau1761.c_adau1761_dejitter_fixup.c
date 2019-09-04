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
struct snd_soc_dapm_widget {int /*<<< orphan*/  dapm; } ;
struct snd_soc_component {int dummy; } ;
struct snd_kcontrol {int dummy; } ;
struct adau {int /*<<< orphan*/  regmap; int /*<<< orphan*/  master; } ;

/* Variables and functions */
 int /*<<< orphan*/  ADAU1761_DEJITTER ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct adau* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 struct snd_soc_component* snd_soc_dapm_to_component (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int adau1761_dejitter_fixup(struct snd_soc_dapm_widget *w,
	struct snd_kcontrol *kcontrol, int event)
{
	struct snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);
	struct adau *adau = snd_soc_component_get_drvdata(component);

	/* After any power changes have been made the dejitter circuit
	 * has to be reinitialized. */
	regmap_write(adau->regmap, ADAU1761_DEJITTER, 0);
	if (!adau->master)
		regmap_write(adau->regmap, ADAU1761_DEJITTER, 3);

	return 0;
}