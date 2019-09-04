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
struct dma_features {int frpbs; int frpes; int /*<<< orphan*/  frpsel; } ;
struct stmmac_priv {int tc_off_max; unsigned int tc_entries_max; int /*<<< orphan*/  device; int /*<<< orphan*/ * tc_entries; struct dma_features dma_cap; } ;

/* Variables and functions */
 int EINVAL ; 
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  dev_info (int /*<<< orphan*/ ,char*,unsigned int,int) ; 
 int /*<<< orphan*/ * devm_kcalloc (int /*<<< orphan*/ ,unsigned int,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tc_fill_all_pass_entry (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int tc_init(struct stmmac_priv *priv)
{
	struct dma_features *dma_cap = &priv->dma_cap;
	unsigned int count;

	if (!dma_cap->frpsel)
		return -EINVAL;

	switch (dma_cap->frpbs) {
	case 0x0:
		priv->tc_off_max = 64;
		break;
	case 0x1:
		priv->tc_off_max = 128;
		break;
	case 0x2:
		priv->tc_off_max = 256;
		break;
	default:
		return -EINVAL;
	}

	switch (dma_cap->frpes) {
	case 0x0:
		count = 64;
		break;
	case 0x1:
		count = 128;
		break;
	case 0x2:
		count = 256;
		break;
	default:
		return -EINVAL;
	}

	/* Reserve one last filter which lets all pass */
	priv->tc_entries_max = count;
	priv->tc_entries = devm_kcalloc(priv->device,
			count, sizeof(*priv->tc_entries), GFP_KERNEL);
	if (!priv->tc_entries)
		return -ENOMEM;

	tc_fill_all_pass_entry(&priv->tc_entries[count - 1]);

	dev_info(priv->device, "Enabling HW TC (entries=%d, max_off=%d)\n",
			priv->tc_entries_max, priv->tc_off_max);
	return 0;
}