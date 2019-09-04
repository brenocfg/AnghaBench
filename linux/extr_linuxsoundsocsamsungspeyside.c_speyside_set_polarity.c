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
struct snd_soc_component {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  WM8996_HPSEL_GPIO ; 
 int /*<<< orphan*/  gpio_direction_output (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  snd_soc_component_get_dapm (struct snd_soc_component*) ; 
 int /*<<< orphan*/  snd_soc_dapm_sync (int /*<<< orphan*/ ) ; 
 int speyside_jack_polarity ; 

__attribute__((used)) static void speyside_set_polarity(struct snd_soc_component *component,
				  int polarity)
{
	speyside_jack_polarity = !polarity;
	gpio_direction_output(WM8996_HPSEL_GPIO, speyside_jack_polarity);

	/* Re-run DAPM to make sure we're using the correct mic bias */
	snd_soc_dapm_sync(snd_soc_component_get_dapm(component));
}