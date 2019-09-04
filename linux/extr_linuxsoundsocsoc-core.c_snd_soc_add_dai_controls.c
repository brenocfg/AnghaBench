#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct snd_soc_dai {int /*<<< orphan*/  dev; TYPE_2__* component; } ;
struct snd_kcontrol_new {int dummy; } ;
struct snd_card {int dummy; } ;
struct TYPE_4__ {TYPE_1__* card; } ;
struct TYPE_3__ {struct snd_card* snd_card; } ;

/* Variables and functions */
 int snd_soc_add_controls (struct snd_card*,int /*<<< orphan*/ ,struct snd_kcontrol_new const*,int,int /*<<< orphan*/ *,struct snd_soc_dai*) ; 

int snd_soc_add_dai_controls(struct snd_soc_dai *dai,
	const struct snd_kcontrol_new *controls, int num_controls)
{
	struct snd_card *card = dai->component->card->snd_card;

	return snd_soc_add_controls(card, dai->dev, controls, num_controls,
			NULL, dai);
}