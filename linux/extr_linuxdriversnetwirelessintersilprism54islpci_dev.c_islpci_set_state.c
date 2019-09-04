#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
typedef  int islpci_state_t ;
struct TYPE_3__ {int state; scalar_t__ state_off; } ;
typedef  TYPE_1__ islpci_private ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int) ; 
#define  PRV_STATE_OFF 129 
#define  PRV_STATE_PREBOOT 128 

islpci_state_t
islpci_set_state(islpci_private *priv, islpci_state_t new_state)
{
	islpci_state_t old_state;

	/* lock */
	old_state = priv->state;

	/* this means either a race condition or some serious error in
	 * the driver code */
	switch (new_state) {
	case PRV_STATE_OFF:
		priv->state_off++;
	default:
		priv->state = new_state;
		break;

	case PRV_STATE_PREBOOT:
		/* there are actually many off-states, enumerated by
		 * state_off */
		if (old_state == PRV_STATE_OFF)
			priv->state_off--;

		/* only if hw_unavailable is zero now it means we either
		 * were in off#1 state, or came here from
		 * somewhere else */
		if (!priv->state_off)
			priv->state = new_state;
		break;
	}
#if 0
	printk(KERN_DEBUG "%s: state transition %d -> %d (off#%d)\n",
	       priv->ndev->name, old_state, new_state, priv->state_off);
#endif

	/* invariants */
	BUG_ON(priv->state_off < 0);
	BUG_ON(priv->state_off && (priv->state != PRV_STATE_OFF));
	BUG_ON(!priv->state_off && (priv->state == PRV_STATE_OFF));

	/* unlock */
	return old_state;
}