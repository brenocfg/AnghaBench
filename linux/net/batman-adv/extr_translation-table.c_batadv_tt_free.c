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
struct TYPE_2__ {int /*<<< orphan*/  last_changeset; int /*<<< orphan*/  work; } ;
struct batadv_priv {TYPE_1__ tt; } ;

/* Variables and functions */
 int /*<<< orphan*/  BATADV_TVLV_ROAM ; 
 int /*<<< orphan*/  BATADV_TVLV_TT ; 
 int /*<<< orphan*/  batadv_tt_changes_list_free (struct batadv_priv*) ; 
 int /*<<< orphan*/  batadv_tt_global_table_free (struct batadv_priv*) ; 
 int /*<<< orphan*/  batadv_tt_local_table_free (struct batadv_priv*) ; 
 int /*<<< orphan*/  batadv_tt_req_list_free (struct batadv_priv*) ; 
 int /*<<< orphan*/  batadv_tt_roam_list_free (struct batadv_priv*) ; 
 int /*<<< orphan*/  batadv_tvlv_container_unregister (struct batadv_priv*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  batadv_tvlv_handler_unregister (struct batadv_priv*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 

void batadv_tt_free(struct batadv_priv *bat_priv)
{
	batadv_tvlv_handler_unregister(bat_priv, BATADV_TVLV_ROAM, 1);

	batadv_tvlv_container_unregister(bat_priv, BATADV_TVLV_TT, 1);
	batadv_tvlv_handler_unregister(bat_priv, BATADV_TVLV_TT, 1);

	cancel_delayed_work_sync(&bat_priv->tt.work);

	batadv_tt_local_table_free(bat_priv);
	batadv_tt_global_table_free(bat_priv);
	batadv_tt_req_list_free(bat_priv);
	batadv_tt_changes_list_free(bat_priv);
	batadv_tt_roam_list_free(bat_priv);

	kfree(bat_priv->tt.last_changeset);
}