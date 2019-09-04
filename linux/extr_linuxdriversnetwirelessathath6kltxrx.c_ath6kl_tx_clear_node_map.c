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
typedef  size_t u32 ;
struct ath6kl_vif {scalar_t__ nw_type; struct ath6kl* ar; } ;
struct ath6kl_node_mapping {int dummy; } ;
struct ath6kl {int ctrl_ep; int node_num; TYPE_1__* node_map; int /*<<< orphan*/  ibss_ps_enable; } ;
typedef  enum htc_endpoint_id { ____Placeholder_htc_endpoint_id } htc_endpoint_id ;
struct TYPE_2__ {scalar_t__ tx_pend; } ;

/* Variables and functions */
 scalar_t__ ADHOC_NETWORK ; 
 int /*<<< orphan*/  memset (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void ath6kl_tx_clear_node_map(struct ath6kl_vif *vif,
				     enum htc_endpoint_id eid, u32 map_no)
{
	struct ath6kl *ar = vif->ar;
	u32 i;

	if (vif->nw_type != ADHOC_NETWORK)
		return;

	if (!ar->ibss_ps_enable)
		return;

	if (eid == ar->ctrl_ep)
		return;

	if (map_no == 0)
		return;

	map_no--;
	ar->node_map[map_no].tx_pend--;

	if (ar->node_map[map_no].tx_pend)
		return;

	if (map_no != (ar->node_num - 1))
		return;

	for (i = ar->node_num; i > 0; i--) {
		if (ar->node_map[i - 1].tx_pend)
			break;

		memset(&ar->node_map[i - 1], 0,
		       sizeof(struct ath6kl_node_mapping));
		ar->node_num--;
	}
}