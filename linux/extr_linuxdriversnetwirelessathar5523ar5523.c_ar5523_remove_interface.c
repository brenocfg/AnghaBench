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
struct ieee80211_vif {int dummy; } ;
struct ieee80211_hw {struct ar5523* priv; } ;
struct ar5523 {int /*<<< orphan*/ * vif; } ;

/* Variables and functions */
 int /*<<< orphan*/  ar5523_dbg (struct ar5523*,char*) ; 

__attribute__((used)) static void ar5523_remove_interface(struct ieee80211_hw *hw,
				    struct ieee80211_vif *vif)
{
	struct ar5523 *ar = hw->priv;

	ar5523_dbg(ar, "remove interface called\n");
	ar->vif = NULL;
}