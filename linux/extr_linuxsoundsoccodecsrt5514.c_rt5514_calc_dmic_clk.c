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
 int ARRAY_SIZE (int*) ; 
 int EINVAL ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  pr_warn (char*,int) ; 

__attribute__((used)) static int rt5514_calc_dmic_clk(struct snd_soc_component *component, int rate)
{
	int div[] = {2, 3, 4, 8, 12, 16, 24, 32};
	int i;

	if (rate < 1000000 * div[0]) {
		pr_warn("Base clock rate %d is too low\n", rate);
		return -EINVAL;
	}

	for (i = 0; i < ARRAY_SIZE(div); i++) {
		/* find divider that gives DMIC frequency below 3.072MHz */
		if (3072000 * div[i] >= rate)
			return i;
	}

	dev_warn(component->dev, "Base clock rate %d is too high\n", rate);
	return -EINVAL;
}