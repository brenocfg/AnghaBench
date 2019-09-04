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
struct wm_adsp {char* name; struct snd_soc_component* component; } ;
struct snd_soc_component {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (char*) ; 
 int /*<<< orphan*/  snd_soc_component_disable_pin (struct snd_soc_component*,char*) ; 
 int /*<<< orphan*/  snprintf (char*,int /*<<< orphan*/ ,char*,char*) ; 
 int /*<<< orphan*/  wm_adsp2_init_debugfs (struct wm_adsp*,struct snd_soc_component*) ; 

int wm_adsp2_component_probe(struct wm_adsp *dsp, struct snd_soc_component *component)
{
	char preload[32];

	snprintf(preload, ARRAY_SIZE(preload), "%s Preload", dsp->name);
	snd_soc_component_disable_pin(component, preload);

	wm_adsp2_init_debugfs(dsp, component);

	dsp->component = component;

	return 0;
}