#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct snd_soc_jack {int dummy; } ;
struct snd_soc_component {int dummy; } ;
struct da7219_priv {TYPE_1__* aad; } ;
struct TYPE_2__ {int jack_inserted; struct snd_soc_jack* jack; } ;

/* Variables and functions */
 int /*<<< orphan*/  DA7219_AAD_REPORT_ALL_MASK ; 
 int /*<<< orphan*/  DA7219_ACCDET_CONFIG_1 ; 
 int /*<<< orphan*/  DA7219_ACCDET_EN_MASK ; 
 struct da7219_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_jack_report (struct snd_soc_jack*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void da7219_aad_jack_det(struct snd_soc_component *component, struct snd_soc_jack *jack)
{
	struct da7219_priv *da7219 = snd_soc_component_get_drvdata(component);

	da7219->aad->jack = jack;
	da7219->aad->jack_inserted = false;

	/* Send an initial empty report */
	snd_soc_jack_report(jack, 0, DA7219_AAD_REPORT_ALL_MASK);

	/* Enable/Disable jack detection */
	snd_soc_component_update_bits(component, DA7219_ACCDET_CONFIG_1,
			    DA7219_ACCDET_EN_MASK,
			    (jack ? DA7219_ACCDET_EN_MASK : 0));
}