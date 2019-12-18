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
struct tas2552_data {unsigned int tdm_delay; } ;
struct snd_soc_dai {struct snd_soc_component* component; } ;
struct snd_soc_component {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int /*<<< orphan*/  TAS2552_DOUT ; 
 int /*<<< orphan*/  TAS2552_SDOUT_TRISTATE ; 
 unsigned int __ffs (unsigned int) ; 
 unsigned int __fls (unsigned int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 struct tas2552_data* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int tas2552_set_dai_tdm_slot(struct snd_soc_dai *dai,
				    unsigned int tx_mask, unsigned int rx_mask,
				    int slots, int slot_width)
{
	struct snd_soc_component *component = dai->component;
	struct tas2552_data *tas2552 = snd_soc_component_get_drvdata(component);
	unsigned int lsb;

	if (unlikely(!tx_mask)) {
		dev_err(component->dev, "tx masks need to be non 0\n");
		return -EINVAL;
	}

	/* TDM based on DSP mode requires slots to be adjacent */
	lsb = __ffs(tx_mask);
	if ((lsb + 1) != __fls(tx_mask)) {
		dev_err(component->dev, "Invalid mask, slots must be adjacent\n");
		return -EINVAL;
	}

	tas2552->tdm_delay = lsb * slot_width;

	/* DOUT in high-impedance on inactive bit clocks */
	snd_soc_component_update_bits(component, TAS2552_DOUT,
			    TAS2552_SDOUT_TRISTATE, TAS2552_SDOUT_TRISTATE);

	return 0;
}