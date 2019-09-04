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
struct TYPE_4__ {int /*<<< orphan*/  dev; } ;
struct TYPE_3__ {struct snd_soc_component* component; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARIZONA_CLK_32K_SRC_MASK ; 
 int /*<<< orphan*/  ARIZONA_CLK_SRC_FLL1 ; 
 int /*<<< orphan*/  ARIZONA_CLK_SYSCLK ; 
 int /*<<< orphan*/  ARIZONA_CLOCK_32K_1 ; 
 int /*<<< orphan*/  SND_SOC_CLOCK_IN ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ rpi_cirrus_clear_flls (TYPE_2__*,struct snd_soc_component*) ; 
 int snd_soc_component_set_sysclk (struct snd_soc_component*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int rpi_cirrus_init_wm5102(struct snd_soc_pcm_runtime *rtd)
{
	struct snd_soc_component *component = rtd->codec_dai->component;
	int ret;

	/* no 32kHz input, derive it from sysclk if needed  */
	snd_soc_component_update_bits(component,
			ARIZONA_CLOCK_32K_1, ARIZONA_CLK_32K_SRC_MASK, 2);

	if (rpi_cirrus_clear_flls(rtd->card, component))
		dev_warn(rtd->card->dev,
			"init_wm5102: failed to clear FLLs\n");

	ret = snd_soc_component_set_sysclk(component,
		ARIZONA_CLK_SYSCLK, ARIZONA_CLK_SRC_FLL1,
		0, SND_SOC_CLOCK_IN);
	if (ret) {
		dev_err(rtd->card->dev,
			"Failed to set SYSCLK to Zero: %d\n", ret);
		return ret;
	}

	return 0;
}