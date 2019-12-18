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
struct snd_soc_dapm_context {TYPE_1__* component; } ;
struct nau8824 {struct snd_soc_dapm_context* dapm; } ;
typedef  int /*<<< orphan*/  prefixed_pin ;
struct TYPE_2__ {char* name_prefix; } ;

/* Variables and functions */
 int /*<<< orphan*/  snd_soc_dapm_force_enable_pin (struct snd_soc_dapm_context*,char const*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,char const*,char const*) ; 

__attribute__((used)) static void nau8824_dapm_enable_pin(struct nau8824 *nau8824, const char *pin)
{
	struct snd_soc_dapm_context *dapm = nau8824->dapm;
	const char *prefix = dapm->component->name_prefix;
	char prefixed_pin[80];

	if (prefix) {
		snprintf(prefixed_pin, sizeof(prefixed_pin), "%s %s",
			 prefix, pin);
		snd_soc_dapm_force_enable_pin(dapm, prefixed_pin);
	} else {
		snd_soc_dapm_force_enable_pin(dapm, pin);
	}
}