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
struct wsm_reset {int reset_statistics; int /*<<< orphan*/  link_id; } ;
struct ieee80211_bss_conf {scalar_t__ beacon_int; } ;
struct cw1200_common {scalar_t__ mode; scalar_t__ join_status; scalar_t__ beacon_int; TYPE_1__* vif; } ;
struct TYPE_2__ {struct ieee80211_bss_conf bss_conf; } ;

/* Variables and functions */
 scalar_t__ CW1200_JOIN_STATUS_AP ; 
 scalar_t__ CW1200_JOIN_STATUS_PASSIVE ; 
 scalar_t__ NL80211_IFTYPE_AP ; 
 int /*<<< orphan*/  cw1200_start_ap (struct cw1200_common*) ; 
 int /*<<< orphan*/  pr_debug (char*,...) ; 
 int /*<<< orphan*/  wsm_lock_tx (struct cw1200_common*) ; 
 int /*<<< orphan*/  wsm_reset (struct cw1200_common*,struct wsm_reset*) ; 
 int /*<<< orphan*/  wsm_unlock_tx (struct cw1200_common*) ; 

__attribute__((used)) static int cw1200_update_beaconing(struct cw1200_common *priv)
{
	struct ieee80211_bss_conf *conf = &priv->vif->bss_conf;
	struct wsm_reset reset = {
		.link_id = 0,
		.reset_statistics = true,
	};

	if (priv->mode == NL80211_IFTYPE_AP) {
		/* TODO: check if changed channel, band */
		if (priv->join_status != CW1200_JOIN_STATUS_AP ||
		    priv->beacon_int != conf->beacon_int) {
			pr_debug("ap restarting\n");
			wsm_lock_tx(priv);
			if (priv->join_status != CW1200_JOIN_STATUS_PASSIVE)
				wsm_reset(priv, &reset);
			priv->join_status = CW1200_JOIN_STATUS_PASSIVE;
			cw1200_start_ap(priv);
			wsm_unlock_tx(priv);
		} else
			pr_debug("ap started join_status: %d\n",
				 priv->join_status);
	}
	return 0;
}