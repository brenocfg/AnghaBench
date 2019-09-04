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
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_2__ {int txpower; } ;
struct ieee80211_vif {TYPE_1__ bss_conf; } ;

/* Variables and functions */

__attribute__((used)) static void ath9k_tpc_vif_iter(void *data, u8 *mac, struct ieee80211_vif *vif)
{
	int *power = data;

	if (*power < vif->bss_conf.txpower)
		*power = vif->bss_conf.txpower;
}