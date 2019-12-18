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
struct snd_soc_dai {int probed; int /*<<< orphan*/  name; int /*<<< orphan*/  dev; TYPE_1__* driver; } ;
struct TYPE_2__ {int probe_order; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 int snd_soc_dai_probe (struct snd_soc_dai*) ; 

__attribute__((used)) static int soc_probe_dai(struct snd_soc_dai *dai, int order)
{
	int ret;

	if (dai->probed ||
	    dai->driver->probe_order != order)
		return 0;

	ret = snd_soc_dai_probe(dai);
	if (ret < 0) {
		dev_err(dai->dev, "ASoC: failed to probe DAI %s: %d\n",
			dai->name, ret);
		return ret;
	}

	dai->probed = 1;

	return 0;
}