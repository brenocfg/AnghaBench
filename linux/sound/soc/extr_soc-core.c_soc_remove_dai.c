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
struct snd_soc_dai {scalar_t__ probed; int /*<<< orphan*/  name; int /*<<< orphan*/  dev; TYPE_1__* driver; } ;
struct TYPE_2__ {int remove_order; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ,int) ; 
 int snd_soc_dai_remove (struct snd_soc_dai*) ; 

__attribute__((used)) static void soc_remove_dai(struct snd_soc_dai *dai, int order)
{
	int err;

	if (!dai || !dai->probed || !dai->driver ||
	    dai->driver->remove_order != order)
		return;

	err = snd_soc_dai_remove(dai);
	if (err < 0)
		dev_err(dai->dev,
			"ASoC: failed to remove %s: %d\n",
			dai->name, err);

	dai->probed = 0;
}