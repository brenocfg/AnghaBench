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
 int /*<<< orphan*/  rt5640_disable_jack_detect (struct snd_soc_component*) ; 
 int /*<<< orphan*/  rt5640_enable_jack_detect (struct snd_soc_component*,struct snd_soc_jack*) ; 

__attribute__((used)) static int rt5640_set_jack(struct snd_soc_component *component,
			   struct snd_soc_jack *jack, void *data)
{
	if (jack)
		rt5640_enable_jack_detect(component, jack);
	else
		rt5640_disable_jack_detect(component);

	return 0;
}