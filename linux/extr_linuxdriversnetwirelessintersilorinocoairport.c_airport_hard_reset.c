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
struct orinoco_private {int dummy; } ;

/* Variables and functions */

__attribute__((used)) static int airport_hard_reset(struct orinoco_private *priv)
{
	/* It would be nice to power cycle the Airport for a real hard
	 * reset, but for some reason although it appears to
	 * re-initialize properly, it falls in a screaming heap
	 * shortly afterwards. */
#if 0
	struct airport *card = priv->card;

	/* Vitally important.  If we don't do this it seems we get an
	 * interrupt somewhere during the power cycle, since
	 * hw_unavailable is already set it doesn't get ACKed, we get
	 * into an interrupt loop and the PMU decides to turn us
	 * off. */
	disable_irq(card->irq);

	pmac_call_feature(PMAC_FTR_AIRPORT_ENABLE,
			  macio_get_of_node(card->mdev), 0, 0);
	ssleep(1);
	pmac_call_feature(PMAC_FTR_AIRPORT_ENABLE,
			  macio_get_of_node(card->mdev), 0, 1);
	ssleep(1);

	enable_irq(card->irq);
	ssleep(1);
#endif

	return 0;
}