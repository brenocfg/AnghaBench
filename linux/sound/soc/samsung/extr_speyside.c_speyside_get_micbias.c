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
struct snd_soc_dapm_widget {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 scalar_t__ speyside_jack_polarity ; 
 scalar_t__ strcmp (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static int speyside_get_micbias(struct snd_soc_dapm_widget *source,
				struct snd_soc_dapm_widget *sink)
{
	if (speyside_jack_polarity && (strcmp(source->name, "MICB1") == 0))
		return 1;
	if (!speyside_jack_polarity && (strcmp(source->name, "MICB2") == 0))
		return 1;

	return 0;
}