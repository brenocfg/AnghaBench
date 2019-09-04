#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/ * widget; } ;
struct TYPE_3__ {int /*<<< orphan*/ * widget; } ;
struct snd_soc_dapm_context {TYPE_2__ path_source_cache; TYPE_1__ path_sink_cache; } ;

/* Variables and functions */

void snd_soc_dapm_reset_cache(struct snd_soc_dapm_context *dapm)
{
	dapm->path_sink_cache.widget = NULL;
	dapm->path_source_cache.widget = NULL;
}