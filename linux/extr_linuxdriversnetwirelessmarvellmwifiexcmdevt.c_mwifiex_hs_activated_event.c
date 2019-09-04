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
typedef  scalar_t__ u8 ;
struct mwifiex_private {TYPE_1__* adapter; } ;
struct TYPE_3__ {int hs_activated; int hs_activate_wait_q_woken; int /*<<< orphan*/  hs_activate_wait_q; int /*<<< orphan*/  work_flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  EVENT ; 
 int /*<<< orphan*/  MWIFIEX_IS_HS_CONFIGURED ; 
 int /*<<< orphan*/  RXREOR_FORCE_NO_DROP ; 
 int /*<<< orphan*/  mwifiex_dbg (TYPE_1__*,int /*<<< orphan*/ ,char*) ; 
 int /*<<< orphan*/  mwifiex_update_rxreor_flags (TYPE_1__*,int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wake_up_interruptible (int /*<<< orphan*/ *) ; 

void
mwifiex_hs_activated_event(struct mwifiex_private *priv, u8 activated)
{
	if (activated) {
		if (test_bit(MWIFIEX_IS_HS_CONFIGURED,
			     &priv->adapter->work_flags)) {
			priv->adapter->hs_activated = true;
			mwifiex_update_rxreor_flags(priv->adapter,
						    RXREOR_FORCE_NO_DROP);
			mwifiex_dbg(priv->adapter, EVENT,
				    "event: hs_activated\n");
			priv->adapter->hs_activate_wait_q_woken = true;
			wake_up_interruptible(
				&priv->adapter->hs_activate_wait_q);
		} else {
			mwifiex_dbg(priv->adapter, EVENT,
				    "event: HS not configured\n");
		}
	} else {
		mwifiex_dbg(priv->adapter, EVENT,
			    "event: hs_deactivated\n");
		priv->adapter->hs_activated = false;
	}
}