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
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int sst_fill_ssp_slot (struct snd_soc_dai*,unsigned int,unsigned int,int,int) ; 

__attribute__((used)) static int sst_platform_set_ssp_slot(struct snd_soc_dai *dai,
			unsigned int tx_mask, unsigned int rx_mask,
			int slots, int slot_width) {
	int ret = 0;

	if (!dai->active)
		return ret;

	ret = sst_fill_ssp_slot(dai, tx_mask, rx_mask, slots, slot_width);
	if (ret < 0)
		dev_err(dai->dev, "sst_fill_ssp_slot failed..%d\n", ret);

	return ret;
}