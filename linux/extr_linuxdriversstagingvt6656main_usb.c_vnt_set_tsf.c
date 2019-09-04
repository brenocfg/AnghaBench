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
typedef  int /*<<< orphan*/  u64 ;
struct vnt_private {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  beacon_int; } ;
struct ieee80211_vif {TYPE_1__ bss_conf; } ;
struct ieee80211_hw {struct vnt_private* priv; } ;

/* Variables and functions */
 int /*<<< orphan*/  vnt_update_next_tbtt (struct vnt_private*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void vnt_set_tsf(struct ieee80211_hw *hw, struct ieee80211_vif *vif,
			u64 tsf)
{
	struct vnt_private *priv = hw->priv;

	vnt_update_next_tbtt(priv, tsf, vif->bss_conf.beacon_int);
}