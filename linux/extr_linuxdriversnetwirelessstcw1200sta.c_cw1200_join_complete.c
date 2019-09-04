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
struct cw1200_common {int join_pending; scalar_t__ mode; int /*<<< orphan*/  join_status; int /*<<< orphan*/  vif; int /*<<< orphan*/  listening; scalar_t__ join_complete_status; } ;

/* Variables and functions */
 int /*<<< orphan*/  CW1200_JOIN_STATUS_IBSS ; 
 int /*<<< orphan*/  CW1200_JOIN_STATUS_PASSIVE ; 
 int /*<<< orphan*/  CW1200_JOIN_STATUS_PRE_STA ; 
 scalar_t__ NL80211_IFTYPE_ADHOC ; 
 int /*<<< orphan*/  cw1200_do_unjoin (struct cw1200_common*) ; 
 int /*<<< orphan*/  cw1200_update_listening (struct cw1200_common*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_connection_loss (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pr_debug (char*,scalar_t__) ; 
 int /*<<< orphan*/  wsm_unlock_tx (struct cw1200_common*) ; 

__attribute__((used)) static void cw1200_join_complete(struct cw1200_common *priv)
{
	pr_debug("[STA] Join complete (%d)\n", priv->join_complete_status);

	priv->join_pending = false;
	if (priv->join_complete_status) {
		priv->join_status = CW1200_JOIN_STATUS_PASSIVE;
		cw1200_update_listening(priv, priv->listening);
		cw1200_do_unjoin(priv);
		ieee80211_connection_loss(priv->vif);
	} else {
		if (priv->mode == NL80211_IFTYPE_ADHOC)
			priv->join_status = CW1200_JOIN_STATUS_IBSS;
		else
			priv->join_status = CW1200_JOIN_STATUS_PRE_STA;
	}
	wsm_unlock_tx(priv); /* Clearing the lock held before do_join() */
}