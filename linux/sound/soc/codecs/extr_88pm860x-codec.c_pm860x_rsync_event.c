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
struct snd_soc_dapm_widget {int /*<<< orphan*/  dapm; } ;
struct snd_soc_component {int dummy; } ;
struct snd_kcontrol {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  DAC_MUTE ; 
 int /*<<< orphan*/  PM860X_DAC_OFFSET ; 
 int /*<<< orphan*/  PM860X_EAR_CTRL_2 ; 
 int /*<<< orphan*/  RSYNC_CHANGE ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct snd_soc_component* snd_soc_dapm_to_component (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int pm860x_rsync_event(struct snd_soc_dapm_widget *w,
			      struct snd_kcontrol *kcontrol, int event)
{
	struct snd_soc_component *component = snd_soc_dapm_to_component(w->dapm);

	/*
	 * In order to avoid current on the load, mute power-on and power-off
	 * should be transients.
	 * Unmute by DAC_MUTE. It should be unmuted when DAPM sequence is
	 * finished.
	 */
	snd_soc_component_update_bits(component, PM860X_DAC_OFFSET, DAC_MUTE, 0);
	snd_soc_component_update_bits(component, PM860X_EAR_CTRL_2,
			    RSYNC_CHANGE, RSYNC_CHANGE);
	return 0;
}