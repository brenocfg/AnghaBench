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
struct lbs_private {int fw_ready; struct if_cs_card* card; } ;
struct if_cs_card {scalar_t__ model; TYPE_1__* p_dev; } ;
struct firmware {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  irq; } ;

/* Variables and functions */
 int /*<<< orphan*/  DRV_NAME ; 
 int /*<<< orphan*/  IF_CS_BIT_MASK ; 
 int /*<<< orphan*/  IF_CS_CARD_INT_CAUSE ; 
 int /*<<< orphan*/  IRQF_SHARED ; 
 scalar_t__ MODEL_8305 ; 
 int /*<<< orphan*/  free_irq (int /*<<< orphan*/ ,struct if_cs_card*) ; 
 int /*<<< orphan*/  if_cs_enable_ints (struct if_cs_card*) ; 
 int /*<<< orphan*/  if_cs_interrupt ; 
 int if_cs_prog_helper (struct if_cs_card*,struct firmware const*) ; 
 int if_cs_prog_real (struct if_cs_card*,struct firmware const*) ; 
 int /*<<< orphan*/  if_cs_write16 (struct if_cs_card*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ lbs_start_card (struct lbs_private*) ; 
 int /*<<< orphan*/  pr_err (char*,...) ; 
 int request_irq (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct if_cs_card*) ; 

__attribute__((used)) static void if_cs_prog_firmware(struct lbs_private *priv, int ret,
				 const struct firmware *helper,
				 const struct firmware *mainfw)
{
	struct if_cs_card *card = priv->card;

	if (ret) {
		pr_err("failed to find firmware (%d)\n", ret);
		return;
	}

	/* Load the firmware */
	ret = if_cs_prog_helper(card, helper);
	if (ret == 0 && (card->model != MODEL_8305))
		ret = if_cs_prog_real(card, mainfw);
	if (ret)
		return;

	/* Now actually get the IRQ */
	ret = request_irq(card->p_dev->irq, if_cs_interrupt,
		IRQF_SHARED, DRV_NAME, card);
	if (ret) {
		pr_err("error in request_irq\n");
		return;
	}

	/*
	 * Clear any interrupt cause that happened while sending
	 * firmware/initializing card
	 */
	if_cs_write16(card, IF_CS_CARD_INT_CAUSE, IF_CS_BIT_MASK);
	if_cs_enable_ints(card);

	/* And finally bring the card up */
	priv->fw_ready = 1;
	if (lbs_start_card(priv) != 0) {
		pr_err("could not activate card\n");
		free_irq(card->p_dev->irq, card);
	}
}