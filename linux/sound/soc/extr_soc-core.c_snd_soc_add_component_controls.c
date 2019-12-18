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
struct snd_soc_component {int /*<<< orphan*/  name_prefix; int /*<<< orphan*/  dev; TYPE_1__* card; } ;
struct snd_kcontrol_new {int dummy; } ;
struct snd_card {int dummy; } ;
struct TYPE_2__ {struct snd_card* snd_card; } ;

/* Variables and functions */
 int snd_soc_add_controls (struct snd_card*,int /*<<< orphan*/ ,struct snd_kcontrol_new const*,unsigned int,int /*<<< orphan*/ ,struct snd_soc_component*) ; 

int snd_soc_add_component_controls(struct snd_soc_component *component,
	const struct snd_kcontrol_new *controls, unsigned int num_controls)
{
	struct snd_card *card = component->card->snd_card;

	return snd_soc_add_controls(card, component->dev, controls,
			num_controls, component->name_prefix, component);
}