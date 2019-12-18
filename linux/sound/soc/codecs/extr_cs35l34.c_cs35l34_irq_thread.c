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
struct cs35l34_private {int /*<<< orphan*/  regmap; struct snd_soc_component* component; } ;
typedef  int /*<<< orphan*/  irqreturn_t ;

/* Variables and functions */
 unsigned int CS35L34_ALIVE_ERR ; 
 unsigned int CS35L34_AMP_SHORT ; 
 unsigned int CS35L34_BST_HIGH ; 
 unsigned int CS35L34_CAL_ERR ; 
 int /*<<< orphan*/  CS35L34_CAL_ERR_RLS ; 
 int /*<<< orphan*/  CS35L34_INT_MASK_1 ; 
 int /*<<< orphan*/  CS35L34_INT_MASK_2 ; 
 int /*<<< orphan*/  CS35L34_INT_MASK_3 ; 
 int /*<<< orphan*/  CS35L34_INT_MASK_4 ; 
 int /*<<< orphan*/  CS35L34_INT_STATUS_1 ; 
 int /*<<< orphan*/  CS35L34_INT_STATUS_2 ; 
 int /*<<< orphan*/  CS35L34_INT_STATUS_3 ; 
 int /*<<< orphan*/  CS35L34_INT_STATUS_4 ; 
 unsigned int CS35L34_LBST_SHORT ; 
 unsigned int CS35L34_OTE ; 
 int /*<<< orphan*/  CS35L34_OTE_RLS ; 
 unsigned int CS35L34_OTW ; 
 int /*<<< orphan*/  CS35L34_OTW_RLS ; 
 int /*<<< orphan*/  CS35L34_PDN_ALL ; 
 int /*<<< orphan*/  CS35L34_PDN_AMP ; 
 int /*<<< orphan*/  CS35L34_PROT_RELEASE_CTL ; 
 int /*<<< orphan*/  CS35L34_PWRCTL1 ; 
 int /*<<< orphan*/  CS35L34_PWRCTL2 ; 
 int /*<<< orphan*/  CS35L34_SHORT_RLS ; 
 int /*<<< orphan*/  IRQ_HANDLED ; 
 int /*<<< orphan*/  IRQ_NONE ; 
 int /*<<< orphan*/  dev_crit (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  regmap_read (int /*<<< orphan*/ ,int /*<<< orphan*/ ,unsigned int*) ; 
 int /*<<< orphan*/  regmap_update_bits (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static irqreturn_t cs35l34_irq_thread(int irq, void *data)
{
	struct cs35l34_private *cs35l34 = data;
	struct snd_soc_component *component = cs35l34->component;
	unsigned int sticky1, sticky2, sticky3, sticky4;
	unsigned int mask1, mask2, mask3, mask4, current1;


	/* ack the irq by reading all status registers */
	regmap_read(cs35l34->regmap, CS35L34_INT_STATUS_4, &sticky4);
	regmap_read(cs35l34->regmap, CS35L34_INT_STATUS_3, &sticky3);
	regmap_read(cs35l34->regmap, CS35L34_INT_STATUS_2, &sticky2);
	regmap_read(cs35l34->regmap, CS35L34_INT_STATUS_1, &sticky1);

	regmap_read(cs35l34->regmap, CS35L34_INT_MASK_4, &mask4);
	regmap_read(cs35l34->regmap, CS35L34_INT_MASK_3, &mask3);
	regmap_read(cs35l34->regmap, CS35L34_INT_MASK_2, &mask2);
	regmap_read(cs35l34->regmap, CS35L34_INT_MASK_1, &mask1);

	if (!(sticky1 & ~mask1) && !(sticky2 & ~mask2) && !(sticky3 & ~mask3)
		&& !(sticky4 & ~mask4))
		return IRQ_NONE;

	regmap_read(cs35l34->regmap, CS35L34_INT_STATUS_1, &current1);

	if (sticky1 & CS35L34_CAL_ERR) {
		dev_err(component->dev, "Cal error\n");

		/* error is no longer asserted; safe to reset */
		if (!(current1 & CS35L34_CAL_ERR)) {
			dev_dbg(component->dev, "Cal error release\n");
			regmap_update_bits(cs35l34->regmap,
					CS35L34_PROT_RELEASE_CTL,
					CS35L34_CAL_ERR_RLS, 0);
			regmap_update_bits(cs35l34->regmap,
					CS35L34_PROT_RELEASE_CTL,
					CS35L34_CAL_ERR_RLS,
					CS35L34_CAL_ERR_RLS);
			regmap_update_bits(cs35l34->regmap,
					CS35L34_PROT_RELEASE_CTL,
					CS35L34_CAL_ERR_RLS, 0);
			/* note: amp will re-calibrate on next resume */
		}
	}

	if (sticky1 & CS35L34_ALIVE_ERR)
		dev_err(component->dev, "Alive error\n");

	if (sticky1 & CS35L34_AMP_SHORT) {
		dev_crit(component->dev, "Amp short error\n");

		/* error is no longer asserted; safe to reset */
		if (!(current1 & CS35L34_AMP_SHORT)) {
			dev_dbg(component->dev,
				"Amp short error release\n");
			regmap_update_bits(cs35l34->regmap,
					CS35L34_PROT_RELEASE_CTL,
					CS35L34_SHORT_RLS, 0);
			regmap_update_bits(cs35l34->regmap,
					CS35L34_PROT_RELEASE_CTL,
					CS35L34_SHORT_RLS,
					CS35L34_SHORT_RLS);
			regmap_update_bits(cs35l34->regmap,
					CS35L34_PROT_RELEASE_CTL,
					CS35L34_SHORT_RLS, 0);
		}
	}

	if (sticky1 & CS35L34_OTW) {
		dev_crit(component->dev, "Over temperature warning\n");

		/* error is no longer asserted; safe to reset */
		if (!(current1 & CS35L34_OTW)) {
			dev_dbg(component->dev,
				"Over temperature warning release\n");
			regmap_update_bits(cs35l34->regmap,
					CS35L34_PROT_RELEASE_CTL,
					CS35L34_OTW_RLS, 0);
			regmap_update_bits(cs35l34->regmap,
					CS35L34_PROT_RELEASE_CTL,
					CS35L34_OTW_RLS,
					CS35L34_OTW_RLS);
			regmap_update_bits(cs35l34->regmap,
					CS35L34_PROT_RELEASE_CTL,
					CS35L34_OTW_RLS, 0);
		}
	}

	if (sticky1 & CS35L34_OTE) {
		dev_crit(component->dev, "Over temperature error\n");

		/* error is no longer asserted; safe to reset */
		if (!(current1 & CS35L34_OTE)) {
			dev_dbg(component->dev,
				"Over temperature error release\n");
			regmap_update_bits(cs35l34->regmap,
					CS35L34_PROT_RELEASE_CTL,
					CS35L34_OTE_RLS, 0);
			regmap_update_bits(cs35l34->regmap,
					CS35L34_PROT_RELEASE_CTL,
					CS35L34_OTE_RLS,
					CS35L34_OTE_RLS);
			regmap_update_bits(cs35l34->regmap,
					CS35L34_PROT_RELEASE_CTL,
					CS35L34_OTE_RLS, 0);
		}
	}

	if (sticky3 & CS35L34_BST_HIGH) {
		dev_crit(component->dev, "VBST too high error; powering off!\n");
		regmap_update_bits(cs35l34->regmap, CS35L34_PWRCTL2,
				CS35L34_PDN_AMP, CS35L34_PDN_AMP);
		regmap_update_bits(cs35l34->regmap, CS35L34_PWRCTL1,
				CS35L34_PDN_ALL, CS35L34_PDN_ALL);
	}

	if (sticky3 & CS35L34_LBST_SHORT) {
		dev_crit(component->dev, "LBST short error; powering off!\n");
		regmap_update_bits(cs35l34->regmap, CS35L34_PWRCTL2,
				CS35L34_PDN_AMP, CS35L34_PDN_AMP);
		regmap_update_bits(cs35l34->regmap, CS35L34_PWRCTL1,
				CS35L34_PDN_ALL, CS35L34_PDN_ALL);
	}

	return IRQ_HANDLED;
}