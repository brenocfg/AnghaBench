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
typedef  scalar_t__ u8 ;
struct TYPE_4__ {int /*<<< orphan*/  sel_class; } ;
struct batadv_priv {TYPE_2__ gw; } ;
struct batadv_orig_node {int dummy; } ;
struct batadv_neigh_node {int dummy; } ;
struct TYPE_3__ {scalar_t__ tq_avg; } ;
struct batadv_neigh_ifinfo {TYPE_1__ bat_iv; } ;

/* Variables and functions */
 int /*<<< orphan*/  BATADV_DBG_BATMAN ; 
 int /*<<< orphan*/  BATADV_IF_DEFAULT ; 
 scalar_t__ atomic_read (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  batadv_dbg (int /*<<< orphan*/ ,struct batadv_priv*,char*,scalar_t__,scalar_t__) ; 
 struct batadv_neigh_ifinfo* batadv_neigh_ifinfo_get (struct batadv_neigh_node*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  batadv_neigh_ifinfo_put (struct batadv_neigh_ifinfo*) ; 
 int /*<<< orphan*/  batadv_neigh_node_put (struct batadv_neigh_node*) ; 
 struct batadv_neigh_node* batadv_orig_router_get (struct batadv_orig_node*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool batadv_iv_gw_is_eligible(struct batadv_priv *bat_priv,
				     struct batadv_orig_node *curr_gw_orig,
				     struct batadv_orig_node *orig_node)
{
	struct batadv_neigh_ifinfo *router_orig_ifinfo = NULL;
	struct batadv_neigh_ifinfo *router_gw_ifinfo = NULL;
	struct batadv_neigh_node *router_gw = NULL;
	struct batadv_neigh_node *router_orig = NULL;
	u8 gw_tq_avg, orig_tq_avg;
	bool ret = false;

	/* dynamic re-election is performed only on fast or late switch */
	if (atomic_read(&bat_priv->gw.sel_class) <= 2)
		return false;

	router_gw = batadv_orig_router_get(curr_gw_orig, BATADV_IF_DEFAULT);
	if (!router_gw) {
		ret = true;
		goto out;
	}

	router_gw_ifinfo = batadv_neigh_ifinfo_get(router_gw,
						   BATADV_IF_DEFAULT);
	if (!router_gw_ifinfo) {
		ret = true;
		goto out;
	}

	router_orig = batadv_orig_router_get(orig_node, BATADV_IF_DEFAULT);
	if (!router_orig)
		goto out;

	router_orig_ifinfo = batadv_neigh_ifinfo_get(router_orig,
						     BATADV_IF_DEFAULT);
	if (!router_orig_ifinfo)
		goto out;

	gw_tq_avg = router_gw_ifinfo->bat_iv.tq_avg;
	orig_tq_avg = router_orig_ifinfo->bat_iv.tq_avg;

	/* the TQ value has to be better */
	if (orig_tq_avg < gw_tq_avg)
		goto out;

	/* if the routing class is greater than 3 the value tells us how much
	 * greater the TQ value of the new gateway must be
	 */
	if ((atomic_read(&bat_priv->gw.sel_class) > 3) &&
	    (orig_tq_avg - gw_tq_avg < atomic_read(&bat_priv->gw.sel_class)))
		goto out;

	batadv_dbg(BATADV_DBG_BATMAN, bat_priv,
		   "Restarting gateway selection: better gateway found (tq curr: %i, tq new: %i)\n",
		   gw_tq_avg, orig_tq_avg);

	ret = true;
out:
	if (router_gw_ifinfo)
		batadv_neigh_ifinfo_put(router_gw_ifinfo);
	if (router_orig_ifinfo)
		batadv_neigh_ifinfo_put(router_orig_ifinfo);
	if (router_gw)
		batadv_neigh_node_put(router_gw);
	if (router_orig)
		batadv_neigh_node_put(router_orig);

	return ret;
}