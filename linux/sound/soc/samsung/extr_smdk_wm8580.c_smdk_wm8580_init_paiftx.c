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
 int /*<<< orphan*/  snd_soc_dapm_disable_pin (int /*<<< orphan*/ *,char*) ; 

__attribute__((used)) static int smdk_wm8580_init_paiftx(struct snd_soc_pcm_runtime *rtd)
{
	/* Enabling the microphone requires the fitting of a 0R
	 * resistor to connect the line from the microphone jack.
	 */
	snd_soc_dapm_disable_pin(&rtd->card->dapm, "MicIn");

	return 0;
}