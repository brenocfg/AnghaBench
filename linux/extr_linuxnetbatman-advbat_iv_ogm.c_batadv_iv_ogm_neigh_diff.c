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
typedef  scalar_t__ u8 ;
struct batadv_neigh_node {int dummy; } ;
struct TYPE_2__ {scalar_t__ tq_avg; } ;
struct batadv_neigh_ifinfo {TYPE_1__ bat_iv; } ;
struct batadv_hard_iface {int dummy; } ;

/* Variables and functions */
 struct batadv_neigh_ifinfo* batadv_neigh_ifinfo_get (struct batadv_neigh_node*,struct batadv_hard_iface*) ; 
 int /*<<< orphan*/  batadv_neigh_ifinfo_put (struct batadv_neigh_ifinfo*) ; 

__attribute__((used)) static bool batadv_iv_ogm_neigh_diff(struct batadv_neigh_node *neigh1,
				     struct batadv_hard_iface *if_outgoing1,
				     struct batadv_neigh_node *neigh2,
				     struct batadv_hard_iface *if_outgoing2,
				     int *diff)
{
	struct batadv_neigh_ifinfo *neigh1_ifinfo, *neigh2_ifinfo;
	u8 tq1, tq2;
	bool ret = true;

	neigh1_ifinfo = batadv_neigh_ifinfo_get(neigh1, if_outgoing1);
	neigh2_ifinfo = batadv_neigh_ifinfo_get(neigh2, if_outgoing2);

	if (!neigh1_ifinfo || !neigh2_ifinfo) {
		ret = false;
		goto out;
	}

	tq1 = neigh1_ifinfo->bat_iv.tq_avg;
	tq2 = neigh2_ifinfo->bat_iv.tq_avg;
	*diff = (int)tq1 - (int)tq2;

out:
	if (neigh1_ifinfo)
		batadv_neigh_ifinfo_put(neigh1_ifinfo);
	if (neigh2_ifinfo)
		batadv_neigh_ifinfo_put(neigh2_ifinfo);

	return ret;
}