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
struct snd_soc_card {int /*<<< orphan*/  dev; struct snd_card* snd_card; } ;
struct snd_kcontrol_new {int dummy; } ;
struct snd_card {int dummy; } ;

/* Variables and functions */
 int snd_soc_add_controls (struct snd_card*,int /*<<< orphan*/ ,struct snd_kcontrol_new const*,int,int /*<<< orphan*/ *,struct snd_soc_card*) ; 

int snd_soc_add_card_controls(struct snd_soc_card *soc_card,
	const struct snd_kcontrol_new *controls, int num_controls)
{
	struct snd_card *card = soc_card->snd_card;

	return snd_soc_add_controls(card, soc_card->dev, controls, num_controls,
			NULL, soc_card);
}