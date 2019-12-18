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
struct wm_adsp {int dummy; } ;
struct snd_soc_component {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  wm_adsp2_cleanup_debugfs (struct wm_adsp*) ; 

int wm_adsp2_component_remove(struct wm_adsp *dsp, struct snd_soc_component *component)
{
	wm_adsp2_cleanup_debugfs(dsp);

	return 0;
}