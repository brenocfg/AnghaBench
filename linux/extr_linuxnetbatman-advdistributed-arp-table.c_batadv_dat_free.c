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
struct batadv_priv {TYPE_1__ dat; } ;

/* Variables and functions */
 int /*<<< orphan*/  BATADV_TVLV_DAT ; 
 int /*<<< orphan*/  batadv_dat_hash_free (struct batadv_priv*) ; 
 int /*<<< orphan*/  batadv_tvlv_container_unregister (struct batadv_priv*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  batadv_tvlv_handler_unregister (struct batadv_priv*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 

void batadv_dat_free(struct batadv_priv *bat_priv)
{
	batadv_tvlv_container_unregister(bat_priv, BATADV_TVLV_DAT, 1);
	batadv_tvlv_handler_unregister(bat_priv, BATADV_TVLV_DAT, 1);

	cancel_delayed_work_sync(&bat_priv->dat.work);

	batadv_dat_hash_free(bat_priv);
}