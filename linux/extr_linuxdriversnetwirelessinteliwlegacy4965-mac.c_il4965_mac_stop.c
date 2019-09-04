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
struct il_priv {int /*<<< orphan*/  workqueue; scalar_t__ is_open; } ;
struct ieee80211_hw {struct il_priv* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  CSR_INT ; 
 int /*<<< orphan*/  D_MAC80211 (char*) ; 
 int /*<<< orphan*/  _il_wr (struct il_priv*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  flush_workqueue (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  il4965_down (struct il_priv*) ; 
 int /*<<< orphan*/  il_enable_rfkill_int (struct il_priv*) ; 

void
il4965_mac_stop(struct ieee80211_hw *hw)
{
	struct il_priv *il = hw->priv;

	D_MAC80211("enter\n");

	if (!il->is_open)
		return;

	il->is_open = 0;

	il4965_down(il);

	flush_workqueue(il->workqueue);

	/* User space software may expect getting rfkill changes
	 * even if interface is down */
	_il_wr(il, CSR_INT, 0xFFFFFFFF);
	il_enable_rfkill_int(il);

	D_MAC80211("leave\n");
}