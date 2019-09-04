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
struct TYPE_2__ {int /*<<< orphan*/ * backbone_hash; int /*<<< orphan*/ * claim_hash; int /*<<< orphan*/  work; } ;
struct batadv_priv {TYPE_1__ bla; } ;
struct batadv_hard_iface {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  batadv_bla_purge_backbone_gw (struct batadv_priv*,int) ; 
 int /*<<< orphan*/  batadv_bla_purge_claims (struct batadv_priv*,struct batadv_hard_iface*,int) ; 
 int /*<<< orphan*/  batadv_hardif_put (struct batadv_hard_iface*) ; 
 int /*<<< orphan*/  batadv_hash_destroy (int /*<<< orphan*/ *) ; 
 struct batadv_hard_iface* batadv_primary_if_get_selected (struct batadv_priv*) ; 
 int /*<<< orphan*/  cancel_delayed_work_sync (int /*<<< orphan*/ *) ; 

void batadv_bla_free(struct batadv_priv *bat_priv)
{
	struct batadv_hard_iface *primary_if;

	cancel_delayed_work_sync(&bat_priv->bla.work);
	primary_if = batadv_primary_if_get_selected(bat_priv);

	if (bat_priv->bla.claim_hash) {
		batadv_bla_purge_claims(bat_priv, primary_if, 1);
		batadv_hash_destroy(bat_priv->bla.claim_hash);
		bat_priv->bla.claim_hash = NULL;
	}
	if (bat_priv->bla.backbone_hash) {
		batadv_bla_purge_backbone_gw(bat_priv, 1);
		batadv_hash_destroy(bat_priv->bla.backbone_hash);
		bat_priv->bla.backbone_hash = NULL;
	}
	if (primary_if)
		batadv_hardif_put(primary_if);
}