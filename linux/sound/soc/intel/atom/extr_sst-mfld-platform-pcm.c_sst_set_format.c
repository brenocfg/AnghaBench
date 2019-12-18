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
struct snd_soc_dai {int /*<<< orphan*/  dev; int /*<<< orphan*/  active; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int sst_fill_ssp_config (struct snd_soc_dai*,unsigned int) ; 

__attribute__((used)) static int sst_set_format(struct snd_soc_dai *dai, unsigned int fmt)
{
	int ret = 0;

	if (!dai->active)
		return 0;

	ret = sst_fill_ssp_config(dai, fmt);
	if (ret < 0)
		dev_err(dai->dev, "sst_set_format failed..\n");

	return ret;
}