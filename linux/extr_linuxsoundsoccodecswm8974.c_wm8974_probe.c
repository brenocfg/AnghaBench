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
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int wm8974_reset (struct snd_soc_component*) ; 

__attribute__((used)) static int wm8974_probe(struct snd_soc_component *component)
{
	int ret = 0;

	ret = wm8974_reset(component);
	if (ret < 0) {
		dev_err(component->dev, "Failed to issue reset\n");
		return ret;
	}

	return 0;
}