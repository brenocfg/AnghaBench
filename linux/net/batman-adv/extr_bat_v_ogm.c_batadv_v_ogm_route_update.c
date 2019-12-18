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
typedef  scalar_t__ u32 ;
struct ethhdr {int /*<<< orphan*/  h_source; } ;
struct batadv_priv {int dummy; } ;
struct batadv_orig_node {int dummy; } ;
struct batadv_ogm2_packet {int dummy; } ;
struct batadv_neigh_node {struct batadv_orig_node* orig_node; } ;
struct TYPE_2__ {scalar_t__ last_seqno; scalar_t__ throughput; } ;
struct batadv_neigh_ifinfo {TYPE_1__ bat_v; } ;
struct batadv_hard_iface {int dummy; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int /*<<< orphan*/  BATADV_DBG_BATMAN ; 
 scalar_t__ BATADV_OGM_MAX_ORIGDIFF ; 
 int /*<<< orphan*/  batadv_dbg (int /*<<< orphan*/ ,struct batadv_priv*,char*) ; 
 struct batadv_neigh_ifinfo* batadv_neigh_ifinfo_get (struct batadv_neigh_node*,struct batadv_hard_iface*) ; 
 int /*<<< orphan*/  batadv_neigh_ifinfo_put (struct batadv_neigh_ifinfo*) ; 
 int /*<<< orphan*/  batadv_neigh_node_put (struct batadv_neigh_node*) ; 
 int /*<<< orphan*/  batadv_orig_node_put (struct batadv_orig_node*) ; 
 struct batadv_neigh_node* batadv_orig_router_get (struct batadv_orig_node*,struct batadv_hard_iface*) ; 
 int /*<<< orphan*/  batadv_update_route (struct batadv_priv*,struct batadv_orig_node*,struct batadv_hard_iface*,struct batadv_neigh_node*) ; 
 struct batadv_orig_node* batadv_v_ogm_orig_get (struct batadv_priv*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool batadv_v_ogm_route_update(struct batadv_priv *bat_priv,
				      const struct ethhdr *ethhdr,
				      const struct batadv_ogm2_packet *ogm2,
				      struct batadv_orig_node *orig_node,
				      struct batadv_neigh_node *neigh_node,
				      struct batadv_hard_iface *if_incoming,
				      struct batadv_hard_iface *if_outgoing)
{
	struct batadv_neigh_node *router = NULL;
	struct batadv_orig_node *orig_neigh_node;
	struct batadv_neigh_node *orig_neigh_router = NULL;
	struct batadv_neigh_ifinfo *router_ifinfo = NULL, *neigh_ifinfo = NULL;
	u32 router_throughput, neigh_throughput;
	u32 router_last_seqno;
	u32 neigh_last_seqno;
	s32 neigh_seq_diff;
	bool forward = false;

	orig_neigh_node = batadv_v_ogm_orig_get(bat_priv, ethhdr->h_source);
	if (!orig_neigh_node)
		goto out;

	orig_neigh_router = batadv_orig_router_get(orig_neigh_node,
						   if_outgoing);

	/* drop packet if sender is not a direct neighbor and if we
	 * don't route towards it
	 */
	router = batadv_orig_router_get(orig_node, if_outgoing);
	if (router && router->orig_node != orig_node && !orig_neigh_router) {
		batadv_dbg(BATADV_DBG_BATMAN, bat_priv,
			   "Drop packet: OGM via unknown neighbor!\n");
		goto out;
	}

	/* Mark the OGM to be considered for forwarding, and update routes
	 * if needed.
	 */
	forward = true;

	batadv_dbg(BATADV_DBG_BATMAN, bat_priv,
		   "Searching and updating originator entry of received packet\n");

	/* if this neighbor already is our next hop there is nothing
	 * to change
	 */
	if (router == neigh_node)
		goto out;

	/* don't consider neighbours with worse throughput.
	 * also switch route if this seqno is BATADV_V_MAX_ORIGDIFF newer than
	 * the last received seqno from our best next hop.
	 */
	if (router) {
		router_ifinfo = batadv_neigh_ifinfo_get(router, if_outgoing);
		neigh_ifinfo = batadv_neigh_ifinfo_get(neigh_node, if_outgoing);

		/* if these are not allocated, something is wrong. */
		if (!router_ifinfo || !neigh_ifinfo)
			goto out;

		neigh_last_seqno = neigh_ifinfo->bat_v.last_seqno;
		router_last_seqno = router_ifinfo->bat_v.last_seqno;
		neigh_seq_diff = neigh_last_seqno - router_last_seqno;
		router_throughput = router_ifinfo->bat_v.throughput;
		neigh_throughput = neigh_ifinfo->bat_v.throughput;

		if (neigh_seq_diff < BATADV_OGM_MAX_ORIGDIFF &&
		    router_throughput >= neigh_throughput)
			goto out;
	}

	batadv_update_route(bat_priv, orig_node, if_outgoing, neigh_node);
out:
	if (router)
		batadv_neigh_node_put(router);
	if (orig_neigh_router)
		batadv_neigh_node_put(orig_neigh_router);
	if (orig_neigh_node)
		batadv_orig_node_put(orig_neigh_node);
	if (router_ifinfo)
		batadv_neigh_ifinfo_put(router_ifinfo);
	if (neigh_ifinfo)
		batadv_neigh_ifinfo_put(neigh_ifinfo);

	return forward;
}