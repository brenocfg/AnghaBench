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
struct ts3a227e {struct snd_soc_jack* jack; } ;
struct snd_soc_jack {int /*<<< orphan*/  jack; } ;
struct snd_soc_component {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  KEY_PLAYPAUSE ; 
 int /*<<< orphan*/  KEY_VOICECOMMAND ; 
 int /*<<< orphan*/  KEY_VOLUMEDOWN ; 
 int /*<<< orphan*/  KEY_VOLUMEUP ; 
 int /*<<< orphan*/  SND_JACK_BTN_0 ; 
 int /*<<< orphan*/  SND_JACK_BTN_1 ; 
 int /*<<< orphan*/  SND_JACK_BTN_2 ; 
 int /*<<< orphan*/  SND_JACK_BTN_3 ; 
 int /*<<< orphan*/  snd_jack_set_key (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ts3a227e* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int /*<<< orphan*/  ts3a227e_jack_report (struct ts3a227e*) ; 

int ts3a227e_enable_jack_detect(struct snd_soc_component *component,
				struct snd_soc_jack *jack)
{
	struct ts3a227e *ts3a227e = snd_soc_component_get_drvdata(component);

	snd_jack_set_key(jack->jack, SND_JACK_BTN_0, KEY_PLAYPAUSE);
	snd_jack_set_key(jack->jack, SND_JACK_BTN_1, KEY_VOICECOMMAND);
	snd_jack_set_key(jack->jack, SND_JACK_BTN_2, KEY_VOLUMEUP);
	snd_jack_set_key(jack->jack, SND_JACK_BTN_3, KEY_VOLUMEDOWN);

	ts3a227e->jack = jack;
	ts3a227e_jack_report(ts3a227e);

	return 0;
}