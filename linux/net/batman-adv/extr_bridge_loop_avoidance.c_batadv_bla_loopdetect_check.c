#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {int dummy; } ;
struct ethhdr {int /*<<< orphan*/  h_source; } ;
struct TYPE_4__ {int /*<<< orphan*/  loopdetect_lasttime; int /*<<< orphan*/  loopdetect_addr; } ;
struct batadv_priv {TYPE_2__ bla; } ;
struct batadv_hard_iface {TYPE_1__* net_dev; } ;
struct batadv_bla_backbone_gw {int /*<<< orphan*/  report_work; } ;
struct TYPE_3__ {int /*<<< orphan*/  dev_addr; } ;

/* Variables and functions */
 int /*<<< orphan*/  BATADV_BLA_LOOPDETECT_TIMEOUT ; 
 int /*<<< orphan*/  batadv_backbone_gw_put (struct batadv_bla_backbone_gw*) ; 
 struct batadv_bla_backbone_gw* batadv_bla_get_backbone_gw (struct batadv_priv*,int /*<<< orphan*/ ,unsigned short,int) ; 
 int /*<<< orphan*/  batadv_compare_eth (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  batadv_event_workqueue ; 
 scalar_t__ batadv_has_timed_out (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ethhdr* eth_hdr (struct sk_buff*) ; 
 int queue_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static bool
batadv_bla_loopdetect_check(struct batadv_priv *bat_priv, struct sk_buff *skb,
			    struct batadv_hard_iface *primary_if,
			    unsigned short vid)
{
	struct batadv_bla_backbone_gw *backbone_gw;
	struct ethhdr *ethhdr;
	bool ret;

	ethhdr = eth_hdr(skb);

	/* Only check for the MAC address and skip more checks here for
	 * performance reasons - this function is on the hotpath, after all.
	 */
	if (!batadv_compare_eth(ethhdr->h_source,
				bat_priv->bla.loopdetect_addr))
		return false;

	/* If the packet came too late, don't forward it on the mesh
	 * but don't consider that as loop. It might be a coincidence.
	 */
	if (batadv_has_timed_out(bat_priv->bla.loopdetect_lasttime,
				 BATADV_BLA_LOOPDETECT_TIMEOUT))
		return true;

	backbone_gw = batadv_bla_get_backbone_gw(bat_priv,
						 primary_if->net_dev->dev_addr,
						 vid, true);
	if (unlikely(!backbone_gw))
		return true;

	ret = queue_work(batadv_event_workqueue, &backbone_gw->report_work);

	/* backbone_gw is unreferenced in the report work function function
	 * if queue_work() call was successful
	 */
	if (!ret)
		batadv_backbone_gw_put(backbone_gw);

	return true;
}