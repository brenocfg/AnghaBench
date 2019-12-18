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
struct snd_soc_jack_pin {int dummy; } ;
struct snd_soc_jack {int /*<<< orphan*/  jack; int /*<<< orphan*/  notifier; int /*<<< orphan*/  jack_zones; int /*<<< orphan*/  pins; struct snd_soc_card* card; int /*<<< orphan*/  mutex; } ;
struct snd_soc_card {int /*<<< orphan*/  snd_card; } ;

/* Variables and functions */
 int /*<<< orphan*/  BLOCKING_INIT_NOTIFIER_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_init (int /*<<< orphan*/ *) ; 
 int snd_jack_new (int /*<<< orphan*/ ,char const*,int,int /*<<< orphan*/ *,int,int) ; 
 int snd_soc_jack_add_pins (struct snd_soc_jack*,unsigned int,struct snd_soc_jack_pin*) ; 

int snd_soc_card_jack_new(struct snd_soc_card *card, const char *id, int type,
	struct snd_soc_jack *jack, struct snd_soc_jack_pin *pins,
	unsigned int num_pins)
{
	int ret;

	mutex_init(&jack->mutex);
	jack->card = card;
	INIT_LIST_HEAD(&jack->pins);
	INIT_LIST_HEAD(&jack->jack_zones);
	BLOCKING_INIT_NOTIFIER_HEAD(&jack->notifier);

	ret = snd_jack_new(card->snd_card, id, type, &jack->jack, false, false);
	if (ret)
		return ret;

	if (num_pins)
		return snd_soc_jack_add_pins(jack, num_pins, pins);

	return 0;
}