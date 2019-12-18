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
struct TYPE_6__ {int /*<<< orphan*/  sel_class; } ;
struct batadv_priv {TYPE_3__ gw; TYPE_2__* algo_ops; } ;
struct TYPE_4__ {int /*<<< orphan*/  (* init_sel_class ) (struct batadv_priv*) ;} ;
struct TYPE_5__ {TYPE_1__ gw; } ;

/* Variables and functions */
 int /*<<< orphan*/  BATADV_TVLV_GW ; 
 int /*<<< orphan*/  BATADV_TVLV_HANDLER_OGM_CIFNOTFND ; 
 int /*<<< orphan*/  atomic_set (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  batadv_gw_tvlv_ogm_handler_v1 ; 
 int /*<<< orphan*/  batadv_tvlv_handler_register (struct batadv_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  stub1 (struct batadv_priv*) ; 

void batadv_gw_init(struct batadv_priv *bat_priv)
{
	if (bat_priv->algo_ops->gw.init_sel_class)
		bat_priv->algo_ops->gw.init_sel_class(bat_priv);
	else
		atomic_set(&bat_priv->gw.sel_class, 1);

	batadv_tvlv_handler_register(bat_priv, batadv_gw_tvlv_ogm_handler_v1,
				     NULL, BATADV_TVLV_GW, 1,
				     BATADV_TVLV_HANDLER_OGM_CIFNOTFND);
}