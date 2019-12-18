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
struct batadv_priv {TYPE_1__ mcast; } ;

/* Variables and functions */
 int /*<<< orphan*/  BATADV_TVLV_HANDLER_OGM_CIFNOTFND ; 
 int /*<<< orphan*/  BATADV_TVLV_MCAST ; 
 int /*<<< orphan*/  INIT_DELAYED_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  batadv_mcast_mla_update ; 
 int /*<<< orphan*/  batadv_mcast_start_timer (struct batadv_priv*) ; 
 int /*<<< orphan*/  batadv_mcast_tvlv_ogm_handler ; 
 int /*<<< orphan*/  batadv_tvlv_handler_register (struct batadv_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 

void batadv_mcast_init(struct batadv_priv *bat_priv)
{
	batadv_tvlv_handler_register(bat_priv, batadv_mcast_tvlv_ogm_handler,
				     NULL, BATADV_TVLV_MCAST, 2,
				     BATADV_TVLV_HANDLER_OGM_CIFNOTFND);

	INIT_DELAYED_WORK(&bat_priv->mcast.work, batadv_mcast_mla_update);
	batadv_mcast_start_timer(bat_priv);
}