#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct ipw_priv {int status; TYPE_2__* ieee; } ;
struct TYPE_3__ {int /*<<< orphan*/  wiphy; } ;
struct TYPE_4__ {TYPE_1__ wdev; } ;

/* Variables and functions */
 int STATUS_RF_KILL_HW ; 
 int ipw_read32 (struct ipw_priv*,int) ; 
 int /*<<< orphan*/  wiphy_rfkill_set_hw_state (int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int rf_kill_active(struct ipw_priv *priv)
{
	if (0 == (ipw_read32(priv, 0x30) & 0x10000)) {
		priv->status |= STATUS_RF_KILL_HW;
		wiphy_rfkill_set_hw_state(priv->ieee->wdev.wiphy, true);
	} else {
		priv->status &= ~STATUS_RF_KILL_HW;
		wiphy_rfkill_set_hw_state(priv->ieee->wdev.wiphy, false);
	}

	return (priv->status & STATUS_RF_KILL_HW) ? 1 : 0;
}