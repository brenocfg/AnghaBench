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
struct snd_soc_jack_pin {int /*<<< orphan*/  mask; int /*<<< orphan*/  pin; int /*<<< orphan*/  list; } ;
struct snd_soc_jack {int /*<<< orphan*/  jack; int /*<<< orphan*/  pins; TYPE_1__* card; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  INIT_LIST_HEAD (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int,...) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_jack_add_new_kctl (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_jack_report (struct snd_soc_jack*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

int snd_soc_jack_add_pins(struct snd_soc_jack *jack, int count,
			  struct snd_soc_jack_pin *pins)
{
	int i;

	for (i = 0; i < count; i++) {
		if (!pins[i].pin) {
			dev_err(jack->card->dev, "ASoC: No name for pin %d\n",
				i);
			return -EINVAL;
		}
		if (!pins[i].mask) {
			dev_err(jack->card->dev, "ASoC: No mask for pin %d"
				" (%s)\n", i, pins[i].pin);
			return -EINVAL;
		}

		INIT_LIST_HEAD(&pins[i].list);
		list_add(&(pins[i].list), &jack->pins);
		snd_jack_add_new_kctl(jack->jack, pins[i].pin, pins[i].mask);
	}

	/* Update to reflect the last reported status; canned jack
	 * implementations are likely to set their state before the
	 * card has an opportunity to associate pins.
	 */
	snd_soc_jack_report(jack, 0, 0);

	return 0;
}