#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  size_t u8 ;
struct wl18xx_priv {scalar_t__ last_fw_rls_idx; } ;
struct wl18xx_fw_status_priv {scalar_t__ fw_release_idx; int /*<<< orphan*/ * released_tx_desc; } ;
struct wl1271 {int /*<<< orphan*/  tx_results_count; TYPE_3__* fw_status; TYPE_1__* links; struct wl18xx_priv* priv; } ;
struct TYPE_5__ {size_t hlid; int /*<<< orphan*/  tx_last_rate_mbps; int /*<<< orphan*/  tx_last_rate; } ;
struct TYPE_6__ {TYPE_2__ counters; scalar_t__ priv; } ;
struct TYPE_4__ {int /*<<< orphan*/  fw_rate_mbps; int /*<<< orphan*/  fw_rate_idx; } ;

/* Variables and functions */
 int /*<<< orphan*/  DEBUG_TX ; 
 int /*<<< orphan*/  WARN_ON (int) ; 
 size_t WL18XX_FW_MAX_TX_STATUS_DESC ; 
 size_t WLCORE_MAX_LINKS ; 
 int /*<<< orphan*/  wl1271_debug (int /*<<< orphan*/ ,char*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  wl1271_error (char*,size_t) ; 
 int /*<<< orphan*/  wl18xx_tx_complete_packet (struct wl1271*,int /*<<< orphan*/ ) ; 

void wl18xx_tx_immediate_complete(struct wl1271 *wl)
{
	struct wl18xx_fw_status_priv *status_priv =
		(struct wl18xx_fw_status_priv *)wl->fw_status->priv;
	struct wl18xx_priv *priv = wl->priv;
	u8 i, hlid;

	/* nothing to do here */
	if (priv->last_fw_rls_idx == status_priv->fw_release_idx)
		return;

	/* update rates per link */
	hlid = wl->fw_status->counters.hlid;

	if (hlid < WLCORE_MAX_LINKS) {
		wl->links[hlid].fw_rate_idx =
				wl->fw_status->counters.tx_last_rate;
		wl->links[hlid].fw_rate_mbps =
				wl->fw_status->counters.tx_last_rate_mbps;
	}

	/* freed Tx descriptors */
	wl1271_debug(DEBUG_TX, "last released desc = %d, current idx = %d",
		     priv->last_fw_rls_idx, status_priv->fw_release_idx);

	if (status_priv->fw_release_idx >= WL18XX_FW_MAX_TX_STATUS_DESC) {
		wl1271_error("invalid desc release index %d",
			     status_priv->fw_release_idx);
		WARN_ON(1);
		return;
	}

	for (i = priv->last_fw_rls_idx;
	     i != status_priv->fw_release_idx;
	     i = (i + 1) % WL18XX_FW_MAX_TX_STATUS_DESC) {
		wl18xx_tx_complete_packet(wl,
			status_priv->released_tx_desc[i]);

		wl->tx_results_count++;
	}

	priv->last_fw_rls_idx = status_priv->fw_release_idx;
}