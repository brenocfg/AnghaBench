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

/* Variables and functions */
 int /*<<< orphan*/  es8316_disable_jack_detect (struct snd_soc_component*) ; 
 int /*<<< orphan*/  es8316_enable_jack_detect (struct snd_soc_component*,struct snd_soc_jack*) ; 

__attribute__((used)) static int es8316_set_jack(struct snd_soc_component *component,
			   struct snd_soc_jack *jack, void *data)
{
	if (jack)
		es8316_enable_jack_detect(component, jack);
	else
		es8316_disable_jack_detect(component);

	return 0;
}