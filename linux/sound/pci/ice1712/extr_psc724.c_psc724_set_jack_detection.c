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
struct snd_ice1712 {struct psc724_spec* spec; } ;
struct psc724_spec {int jack_detect; int /*<<< orphan*/  hp_work; } ;

/* Variables and functions */
 int GPIO_HP_JACK ; 
 int /*<<< orphan*/  JACK_INTERVAL ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  psc724_set_jack_state (struct snd_ice1712*,int) ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int snd_ice1712_gpio_read (struct snd_ice1712*) ; 

__attribute__((used)) static void psc724_set_jack_detection(struct snd_ice1712 *ice, bool on)
{
	struct psc724_spec *spec = ice->spec;

	if (spec->jack_detect == on)
		return;

	spec->jack_detect = on;
	if (on) {
		bool hp_connected = snd_ice1712_gpio_read(ice) & GPIO_HP_JACK;
		psc724_set_jack_state(ice, hp_connected);
		schedule_delayed_work(&spec->hp_work,
					msecs_to_jiffies(JACK_INTERVAL));
	} else
		cancel_delayed_work_sync(&spec->hp_work);
}