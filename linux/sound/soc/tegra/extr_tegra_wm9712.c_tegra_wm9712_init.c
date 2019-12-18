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
struct snd_soc_pcm_runtime {TYPE_1__* card; } ;
struct TYPE_2__ {int /*<<< orphan*/  dapm; } ;

/* Variables and functions */
 int snd_soc_dapm_force_enable_pin (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static int tegra_wm9712_init(struct snd_soc_pcm_runtime *rtd)
{
	return snd_soc_dapm_force_enable_pin(&rtd->card->dapm, "Mic Bias");
}