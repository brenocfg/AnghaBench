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
struct TYPE_2__ {int /*<<< orphan*/  work; } ;
struct batadv_priv {TYPE_1__ tt; } ;

/* Variables and functions */
 int /*<<< orphan*/  BATADV_NO_FLAGS ; 
 int BATADV_TT_REMOTE_MASK ; 
 int BATADV_TT_SYNC_MASK ; 
 int /*<<< orphan*/  BATADV_TT_WORK_PERIOD ; 
 int /*<<< orphan*/  BATADV_TVLV_ROAM ; 
 int /*<<< orphan*/  BATADV_TVLV_TT ; 
 int /*<<< orphan*/  BUILD_BUG_ON (int) ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  batadv_event_workqueue ; 
 int /*<<< orphan*/  batadv_roam_tvlv_unicast_handler_v1 ; 
 int batadv_tt_global_init (struct batadv_priv*) ; 
 int batadv_tt_local_init (struct batadv_priv*) ; 
 int /*<<< orphan*/  batadv_tt_purge ; 
 int /*<<< orphan*/ * batadv_tt_tvlv_ogm_handler_v1 ; 
 int /*<<< orphan*/  batadv_tt_tvlv_unicast_handler_v1 ; 
 int /*<<< orphan*/  batadv_tvlv_handler_register (struct batadv_priv*,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  queue_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

int batadv_tt_init(struct batadv_priv *bat_priv)
{
	int ret;

	/* synchronized flags must be remote */
	BUILD_BUG_ON(!(BATADV_TT_SYNC_MASK & BATADV_TT_REMOTE_MASK));

	ret = batadv_tt_local_init(bat_priv);
	if (ret < 0)
		return ret;

	ret = batadv_tt_global_init(bat_priv);
	if (ret < 0)
		return ret;

	batadv_tvlv_handler_register(bat_priv, batadv_tt_tvlv_ogm_handler_v1,
				     batadv_tt_tvlv_unicast_handler_v1,
				     BATADV_TVLV_TT, 1, BATADV_NO_FLAGS);

	batadv_tvlv_handler_register(bat_priv, NULL,
				     batadv_roam_tvlv_unicast_handler_v1,
				     BATADV_TVLV_ROAM, 1, BATADV_NO_FLAGS);

	INIT_DELAYED_WORK(&bat_priv->tt.work, batadv_tt_purge);
	queue_delayed_work(batadv_event_workqueue, &bat_priv->tt.work,
			   msecs_to_jiffies(BATADV_TT_WORK_PERIOD));

	return 1;
}