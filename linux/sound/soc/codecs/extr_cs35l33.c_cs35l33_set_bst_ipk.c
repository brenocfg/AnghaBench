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
struct cs35l33_private {int /*<<< orphan*/  regmap; } ;

/* Variables and functions */
 int /*<<< orphan*/  CS35L33_BST_PEAK_CTL ; 
 int EINVAL ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,unsigned int) ; 
 int /*<<< orphan*/  regmap_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 struct cs35l33_private* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 

__attribute__((used)) static int cs35l33_set_bst_ipk(struct snd_soc_component *component, unsigned int bst)
{
	struct cs35l33_private *cs35l33 = snd_soc_component_get_drvdata(component);
	int ret = 0, steps = 0;

	/* Boost current in uA */
	if (bst > 3600000 || bst < 1850000) {
		dev_err(component->dev, "Invalid boost current %d\n", bst);
		ret = -EINVAL;
		goto err;
	}

	if (bst % 15625) {
		dev_err(component->dev, "Current not a multiple of 15625uA (%d)\n",
			bst);
		ret = -EINVAL;
		goto err;
	}

	while (bst > 1850000) {
		bst -= 15625;
		steps++;
	}

	regmap_write(cs35l33->regmap, CS35L33_BST_PEAK_CTL,
		steps+0x70);

err:
	return ret;
}