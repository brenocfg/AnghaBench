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
struct snd_soc_dai {struct snd_soc_component* component; } ;
struct snd_soc_component {int /*<<< orphan*/  dev; } ;
struct aic3x_priv {unsigned int tdm_delay; int slot_width; } ;

/* Variables and functions */
 int /*<<< orphan*/  AIC3X_ASD_INTF_CTRLA ; 
 int /*<<< orphan*/  DOUT_TRISTATE ; 
 int EINVAL ; 
 unsigned int __ffs (unsigned int) ; 
 unsigned int __fls (unsigned int) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,...) ; 
 struct aic3x_priv* snd_soc_component_get_drvdata (struct snd_soc_component*) ; 
 int /*<<< orphan*/  snd_soc_component_update_bits (struct snd_soc_component*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static int aic3x_set_dai_tdm_slot(struct snd_soc_dai *codec_dai,
				  unsigned int tx_mask, unsigned int rx_mask,
				  int slots, int slot_width)
{
	struct snd_soc_component *component = codec_dai->component;
	struct aic3x_priv *aic3x = snd_soc_component_get_drvdata(component);
	unsigned int lsb;

	if (tx_mask != rx_mask) {
		dev_err(component->dev, "tx and rx masks must be symmetric\n");
		return -EINVAL;
	}

	if (unlikely(!tx_mask)) {
		dev_err(component->dev, "tx and rx masks need to be non 0\n");
		return -EINVAL;
	}

	/* TDM based on DSP mode requires slots to be adjacent */
	lsb = __ffs(tx_mask);
	if ((lsb + 1) != __fls(tx_mask)) {
		dev_err(component->dev, "Invalid mask, slots must be adjacent\n");
		return -EINVAL;
	}

	switch (slot_width) {
	case 16:
	case 20:
	case 24:
	case 32:
		break;
	default:
		dev_err(component->dev, "Unsupported slot width %d\n", slot_width);
		return -EINVAL;
	}


	aic3x->tdm_delay = lsb;
	aic3x->slot_width = slot_width;

	/* DOUT in high-impedance on inactive bit clocks */
	snd_soc_component_update_bits(component, AIC3X_ASD_INTF_CTRLA,
			    DOUT_TRISTATE, DOUT_TRISTATE);

	return 0;
}