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
struct snd_soc_dapm_widget {int dummy; } ;
struct snd_soc_dapm_wcache {struct snd_soc_dapm_widget* widget; } ;

/* Variables and functions */

__attribute__((used)) static inline void dapm_wcache_update(struct snd_soc_dapm_wcache *wcache,
				      struct snd_soc_dapm_widget *w)
{
	wcache->widget = w;
}