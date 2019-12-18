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
struct batadv_priv {int dummy; } ;
struct batadv_hard_iface {TYPE_1__* net_dev; } ;
struct batadv_bla_backbone_gw {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  BATADV_CLAIM_TYPE_CLAIM ; 
 int /*<<< orphan*/  batadv_backbone_gw_put (struct batadv_bla_backbone_gw*) ; 
 int /*<<< orphan*/  batadv_bla_add_claim (struct batadv_priv*,int /*<<< orphan*/ *,unsigned short,struct batadv_bla_backbone_gw*) ; 
 struct batadv_bla_backbone_gw* batadv_bla_get_backbone_gw (struct batadv_priv*,int /*<<< orphan*/ *,unsigned short,int) ; 
 int /*<<< orphan*/  batadv_bla_send_claim (struct batadv_priv*,int /*<<< orphan*/ *,unsigned short,int /*<<< orphan*/ ) ; 
 scalar_t__ batadv_compare_eth (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static bool batadv_handle_claim(struct batadv_priv *bat_priv,
				struct batadv_hard_iface *primary_if,
				u8 *backbone_addr, u8 *claim_addr,
				unsigned short vid)
{
	struct batadv_bla_backbone_gw *backbone_gw;

	/* register the gateway if not yet available, and add the claim. */

	backbone_gw = batadv_bla_get_backbone_gw(bat_priv, backbone_addr, vid,
						 false);

	if (unlikely(!backbone_gw))
		return true;

	/* this must be a CLAIM frame */
	batadv_bla_add_claim(bat_priv, claim_addr, vid, backbone_gw);
	if (batadv_compare_eth(backbone_addr, primary_if->net_dev->dev_addr))
		batadv_bla_send_claim(bat_priv, claim_addr, vid,
				      BATADV_CLAIM_TYPE_CLAIM);

	/* TODO: we could call something like tt_local_del() here. */

	batadv_backbone_gw_put(backbone_gw);
	return true;
}