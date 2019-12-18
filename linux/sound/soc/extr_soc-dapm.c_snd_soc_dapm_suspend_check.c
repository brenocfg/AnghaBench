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
struct snd_soc_dapm_widget {int ignore_suspend; int /*<<< orphan*/  name; TYPE_2__* dapm; } ;
struct TYPE_4__ {int /*<<< orphan*/  dev; TYPE_1__* card; } ;
struct TYPE_3__ {int /*<<< orphan*/  snd_card; } ;

/* Variables and functions */
#define  SNDRV_CTL_POWER_D3cold 129 
#define  SNDRV_CTL_POWER_D3hot 128 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int snd_power_get_state (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int snd_soc_dapm_suspend_check(struct snd_soc_dapm_widget *widget)
{
	int level = snd_power_get_state(widget->dapm->card->snd_card);

	switch (level) {
	case SNDRV_CTL_POWER_D3hot:
	case SNDRV_CTL_POWER_D3cold:
		if (widget->ignore_suspend)
			dev_dbg(widget->dapm->dev, "ASoC: %s ignoring suspend\n",
				widget->name);
		return widget->ignore_suspend;
	default:
		return 1;
	}
}