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
struct snd_soc_dapm_context {int idle_bias_off; int /*<<< orphan*/  list; int /*<<< orphan*/  dev; int /*<<< orphan*/  suspend_bias_off; int /*<<< orphan*/  bias_level; struct snd_soc_component* component; struct snd_soc_card* card; } ;
struct snd_soc_component {TYPE_1__* driver; int /*<<< orphan*/  dev; } ;
struct snd_soc_card {int /*<<< orphan*/  dapm_list; int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  suspend_bias_off; int /*<<< orphan*/  idle_bias_on; } ;

/* Variables and functions */
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  SND_SOC_BIAS_OFF ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void snd_soc_dapm_init(struct snd_soc_dapm_context *dapm,
		       struct snd_soc_card *card,
		       struct snd_soc_component *component)
{
	dapm->card		= card;
	dapm->component		= component;
	dapm->bias_level	= SND_SOC_BIAS_OFF;

	if (component) {
		dapm->dev		= component->dev;
		dapm->idle_bias_off	= !component->driver->idle_bias_on,
		dapm->suspend_bias_off	= component->driver->suspend_bias_off;
	} else {
		dapm->dev		= card->dev;
	}

	INIT_LIST_HEAD(&dapm->list);
	list_add(&dapm->list, &card->dapm_list);
}