#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
struct ethhdr {int dummy; } ;
struct batadv_priv {int dummy; } ;
struct batadv_orig_node {int dummy; } ;
struct batadv_ogm2_packet {int /*<<< orphan*/  tvlv_len; } ;
struct batadv_neigh_node {int dummy; } ;
struct batadv_hard_iface {int dummy; } ;

/* Variables and functions */
 struct batadv_hard_iface* BATADV_IF_DEFAULT ; 
 int /*<<< orphan*/  batadv_tvlv_containers_process (struct batadv_priv*,int,struct batadv_orig_node*,int /*<<< orphan*/ *,int /*<<< orphan*/ *,unsigned char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  batadv_v_ogm_forward (struct batadv_priv*,struct batadv_ogm2_packet const*,struct batadv_orig_node*,struct batadv_neigh_node*,struct batadv_hard_iface*,struct batadv_hard_iface*) ; 
 int batadv_v_ogm_metric_update (struct batadv_priv*,struct batadv_ogm2_packet const*,struct batadv_orig_node*,struct batadv_neigh_node*,struct batadv_hard_iface*,struct batadv_hard_iface*) ; 
 int batadv_v_ogm_route_update (struct batadv_priv*,struct ethhdr const*,struct batadv_ogm2_packet const*,struct batadv_orig_node*,struct batadv_neigh_node*,struct batadv_hard_iface*,struct batadv_hard_iface*) ; 
 int /*<<< orphan*/  ntohs (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
batadv_v_ogm_process_per_outif(struct batadv_priv *bat_priv,
			       const struct ethhdr *ethhdr,
			       const struct batadv_ogm2_packet *ogm2,
			       struct batadv_orig_node *orig_node,
			       struct batadv_neigh_node *neigh_node,
			       struct batadv_hard_iface *if_incoming,
			       struct batadv_hard_iface *if_outgoing)
{
	int seqno_age;
	bool forward;

	/* first, update the metric with according sanity checks */
	seqno_age = batadv_v_ogm_metric_update(bat_priv, ogm2, orig_node,
					       neigh_node, if_incoming,
					       if_outgoing);

	/* outdated sequence numbers are to be discarded */
	if (seqno_age < 0)
		return;

	/* only unknown & newer OGMs contain TVLVs we are interested in */
	if (seqno_age > 0 && if_outgoing == BATADV_IF_DEFAULT)
		batadv_tvlv_containers_process(bat_priv, true, orig_node,
					       NULL, NULL,
					       (unsigned char *)(ogm2 + 1),
					       ntohs(ogm2->tvlv_len));

	/* if the metric update went through, update routes if needed */
	forward = batadv_v_ogm_route_update(bat_priv, ethhdr, ogm2, orig_node,
					    neigh_node, if_incoming,
					    if_outgoing);

	/* if the routes have been processed correctly, check and forward */
	if (forward)
		batadv_v_ogm_forward(bat_priv, ogm2, orig_node, neigh_node,
				     if_incoming, if_outgoing);
}