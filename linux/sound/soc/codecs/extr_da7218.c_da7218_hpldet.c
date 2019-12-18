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
struct snd_soc_jack {int dummy; } ;
struct snd_soc_component {int dummy; } ;
struct da7218_priv {scalar_t__ dev_id; struct snd_soc_jack* jack; } ;

/* Variables and functions */
 scalar_t__ DA7217_DEV_ID ; 
 int /*<<< orphan*/  DA7218_HPLDET_JACK ; 
 int /*<<< orphan*/  DA7218_HPLDET_JACK_EN_MASK ; 
 int EINVAL ; 
 struct da7218_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int da7218_hpldet(struct snd_soc_component *component, struct snd_soc_jack *jack)
{
	struct da7218_priv *da7218 = snd_soc_component_get_drvdata(component);

	if (da7218->dev_id == DA7217_DEV_ID)
		return -EINVAL;

	da7218->jack = jack;
	snd_soc_component_update_bits(component, DA7218_HPLDET_JACK,
			    DA7218_HPLDET_JACK_EN_MASK,
			    jack ? DA7218_HPLDET_JACK_EN_MASK : 0);

	return 0;
}