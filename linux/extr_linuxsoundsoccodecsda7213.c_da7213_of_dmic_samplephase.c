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
struct snd_soc_component {int /*<<< orphan*/  dev; } ;
typedef  enum da7213_dmic_samplephase { ____Placeholder_da7213_dmic_samplephase } da7213_dmic_samplephase ;

/* Variables and functions */
 int DA7213_DMIC_SAMPLE_BETWEEN_CLKEDGE ; 
 int DA7213_DMIC_SAMPLE_ON_CLKEDGE ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  strcmp (char const*,char*) ; 

__attribute__((used)) static enum da7213_dmic_samplephase
	da7213_of_dmic_samplephase(struct snd_soc_component *component, const char *str)
{
	if (!strcmp(str, "on_clkedge")) {
		return DA7213_DMIC_SAMPLE_ON_CLKEDGE;
	} else if (!strcmp(str, "between_clkedge")) {
		return DA7213_DMIC_SAMPLE_BETWEEN_CLKEDGE;
	} else {
		dev_warn(component->dev, "Invalid DMIC sample phase\n");
		return DA7213_DMIC_SAMPLE_ON_CLKEDGE;
	}
}