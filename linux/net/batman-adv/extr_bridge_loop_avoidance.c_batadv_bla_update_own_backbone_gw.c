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
struct batadv_priv {int dummy; } ;
struct batadv_hard_iface {TYPE_1__* net_dev; } ;
struct batadv_bla_backbone_gw {int /*<<< orphan*/  lasttime; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  batadv_backbone_gw_put (struct batadv_bla_backbone_gw*) ; 
 struct batadv_bla_backbone_gw* batadv_bla_get_backbone_gw (struct batadv_priv*,int /*<<< orphan*/ ,unsigned short,int) ; 
 int /*<<< orphan*/  jiffies ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static void
batadv_bla_update_own_backbone_gw(struct batadv_priv *bat_priv,
				  struct batadv_hard_iface *primary_if,
				  unsigned short vid)
{
	struct batadv_bla_backbone_gw *backbone_gw;

	backbone_gw = batadv_bla_get_backbone_gw(bat_priv,
						 primary_if->net_dev->dev_addr,
						 vid, true);
	if (unlikely(!backbone_gw))
		return;

	backbone_gw->lasttime = jiffies;
	batadv_backbone_gw_put(backbone_gw);
}