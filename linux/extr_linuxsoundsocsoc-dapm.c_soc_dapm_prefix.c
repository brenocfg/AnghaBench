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
struct TYPE_2__ {char const* name_prefix; } ;

/* Variables and functions */

__attribute__((used)) static const char *soc_dapm_prefix(struct snd_soc_dapm_context *dapm)
{
	if (!dapm->component)
		return NULL;
	return dapm->component->name_prefix;
}