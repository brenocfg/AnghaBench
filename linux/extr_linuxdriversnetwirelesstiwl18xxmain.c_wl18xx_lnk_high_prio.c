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
typedef  scalar_t__ u8 ;
struct wl18xx_fw_status_priv {scalar_t__ tx_fast_link_prio_threshold; scalar_t__ tx_slow_link_prio_threshold; int /*<<< orphan*/  link_suspend_bitmap; } ;
struct wl1271_link {scalar_t__ allocated_pkts; } ;
struct wl1271 {unsigned long fw_fast_lnk_map; unsigned long ap_fw_ps_map; TYPE_1__* fw_status; } ;
struct TYPE_2__ {scalar_t__ priv; } ;

/* Variables and functions */
 unsigned long le32_to_cpu (int /*<<< orphan*/ ) ; 
 scalar_t__ test_bit (scalar_t__,unsigned long*) ; 

__attribute__((used)) static bool wl18xx_lnk_high_prio(struct wl1271 *wl, u8 hlid,
				 struct wl1271_link *lnk)
{
	u8 thold;
	struct wl18xx_fw_status_priv *status_priv =
		(struct wl18xx_fw_status_priv *)wl->fw_status->priv;
	unsigned long suspend_bitmap;

	/* if we don't have the link map yet, assume they all low prio */
	if (!status_priv)
		return false;

	/* suspended links are never high priority */
	suspend_bitmap = le32_to_cpu(status_priv->link_suspend_bitmap);
	if (test_bit(hlid, &suspend_bitmap))
		return false;

	/* the priority thresholds are taken from FW */
	if (test_bit(hlid, &wl->fw_fast_lnk_map) &&
	    !test_bit(hlid, &wl->ap_fw_ps_map))
		thold = status_priv->tx_fast_link_prio_threshold;
	else
		thold = status_priv->tx_slow_link_prio_threshold;

	return lnk->allocated_pkts < thold;
}