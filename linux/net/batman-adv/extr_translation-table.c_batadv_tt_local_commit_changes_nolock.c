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
struct TYPE_2__ {int /*<<< orphan*/  ogm_append_cnt; int /*<<< orphan*/  vn; int /*<<< orphan*/  local_changes; int /*<<< orphan*/  commit_lock; } ;
struct batadv_priv {TYPE_1__ tt; } ;

/* Variables and functions */
 int /*<<< orphan*/  BATADV_DBG_TT ; 
 int /*<<< orphan*/  BATADV_TT_CLIENT_NEW ; 
 int /*<<< orphan*/  BATADV_TT_OGM_APPEND_MAX ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  batadv_atomic_dec_not_zero (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  batadv_dbg (int /*<<< orphan*/ ,struct batadv_priv*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  batadv_tt_local_purge_pending_clients (struct batadv_priv*) ; 
 int /*<<< orphan*/  batadv_tt_local_set_flags (struct batadv_priv*,int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  batadv_tt_local_update_crc (struct batadv_priv*) ; 
 int /*<<< orphan*/  batadv_tt_tvlv_container_update (struct batadv_priv*) ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void batadv_tt_local_commit_changes_nolock(struct batadv_priv *bat_priv)
{
	lockdep_assert_held(&bat_priv->tt.commit_lock);

	if (atomic_read(&bat_priv->tt.local_changes) < 1) {
		if (!batadv_atomic_dec_not_zero(&bat_priv->tt.ogm_append_cnt))
			batadv_tt_tvlv_container_update(bat_priv);
		return;
	}

	batadv_tt_local_set_flags(bat_priv, BATADV_TT_CLIENT_NEW, false, true);

	batadv_tt_local_purge_pending_clients(bat_priv);
	batadv_tt_local_update_crc(bat_priv);

	/* Increment the TTVN only once per OGM interval */
	atomic_inc(&bat_priv->tt.vn);
	batadv_dbg(BATADV_DBG_TT, bat_priv,
		   "Local changes committed, updating to ttvn %u\n",
		   (u8)atomic_read(&bat_priv->tt.vn));

	/* reset the sending counter */
	atomic_set(&bat_priv->tt.ogm_append_cnt, BATADV_TT_OGM_APPEND_MAX);
	batadv_tt_tvlv_container_update(bat_priv);
}