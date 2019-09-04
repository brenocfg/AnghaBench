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
struct snd_soc_dapm_context {int dummy; } ;
struct snd_soc_component {int dummy; } ;

/* Variables and functions */
 struct snd_soc_dapm_context* snd_soc_component_get_dapm (struct snd_soc_component*) ; 
 int /*<<< orphan*/  snd_soc_dapm_disable_pin_unlocked (struct snd_soc_dapm_context*,char*) ; 
 int /*<<< orphan*/  snd_soc_dapm_mutex_lock (struct snd_soc_dapm_context*) ; 
 int /*<<< orphan*/  snd_soc_dapm_mutex_unlock (struct snd_soc_dapm_context*) ; 
 int /*<<< orphan*/  snd_soc_dapm_sync_unlocked (struct snd_soc_dapm_context*) ; 

__attribute__((used)) static void rt5651_disable_micbias1_for_ovcd(struct snd_soc_component *component)
{
	struct snd_soc_dapm_context *dapm = snd_soc_component_get_dapm(component);

	snd_soc_dapm_mutex_lock(dapm);
	snd_soc_dapm_disable_pin_unlocked(dapm, "Platform Clock");
	snd_soc_dapm_disable_pin_unlocked(dapm, "micbias1");
	snd_soc_dapm_disable_pin_unlocked(dapm, "LDO");
	snd_soc_dapm_sync_unlocked(dapm);
	snd_soc_dapm_mutex_unlock(dapm);
}