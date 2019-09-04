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
struct snd_soc_dapm_widget_list {int num_widgets; struct snd_soc_dapm_widget** widgets; } ;
struct snd_soc_dapm_widget {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static int widget_in_list(struct snd_soc_dapm_widget_list *list,
		struct snd_soc_dapm_widget *widget)
{
	int i;

	for (i = 0; i < list->num_widgets; i++) {
		if (widget == list->widgets[i])
			return 1;
	}

	return 0;
}