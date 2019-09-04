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
struct snd_soc_pcm_runtime {TYPE_2__* card; TYPE_1__* codec_dai; } ;
struct snd_soc_component {int dummy; } ;
struct TYPE_4__ {int /*<<< orphan*/  dapm; } ;
struct TYPE_3__ {struct snd_soc_component* component; } ;

/* Variables and functions */
 int /*<<< orphan*/  CLKOUT_RATE ; 
 int /*<<< orphan*/  WM9081_SYSCLK_MCLK ; 
 int snd_soc_component_set_sysclk (struct snd_soc_component*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_dapm_nc_pin (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static int lowland_wm9081_init(struct snd_soc_pcm_runtime *rtd)
{
	struct snd_soc_component *component = rtd->codec_dai->component;

	snd_soc_dapm_nc_pin(&rtd->card->dapm, "LINEOUT");

	/* At any time the WM9081 is active it will have this clock */
	return snd_soc_component_set_sysclk(component, WM9081_SYSCLK_MCLK, 0,
					CLKOUT_RATE, 0);
}