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
struct snd_soc_component {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  M98095_089_JACK_DET_AUTO ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int snd_soc_component_write (struct snd_soc_component*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int max98095_jack_detect_disable(struct snd_soc_component *component)
{
	int ret = 0;

	/* configure auto detection to be disabled */
	ret = snd_soc_component_write(component, M98095_089_JACK_DET_AUTO, 0x0);
	if (ret < 0) {
		dev_err(component->dev, "Failed to cfg auto detect %d\n", ret);
		return ret;
	}

	return ret;
}