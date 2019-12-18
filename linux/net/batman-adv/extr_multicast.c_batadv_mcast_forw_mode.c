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
struct sk_buff {int dummy; } ;
struct ethhdr {int /*<<< orphan*/  h_dest; } ;
struct TYPE_2__ {int /*<<< orphan*/  num_want_all_unsnoopables; } ;
struct batadv_priv {int /*<<< orphan*/  multicast_fanout; TYPE_1__ mcast; } ;
struct batadv_orig_node {int dummy; } ;
typedef  enum batadv_forw_mode { ____Placeholder_batadv_forw_mode } batadv_forw_mode ;

/* Variables and functions */
 int BATADV_FORW_ALL ; 
 int BATADV_FORW_NONE ; 
 int BATADV_FORW_SINGLE ; 
 int BATADV_FORW_SOME ; 
 int /*<<< orphan*/  BATADV_NO_FLAGS ; 
 int ENOMEM ; 
 void* atomic_read (int /*<<< orphan*/ *) ; 
 struct batadv_orig_node* batadv_mcast_forw_ip_node_get (struct batadv_priv*,struct ethhdr*) ; 
 int batadv_mcast_forw_mode_check (struct batadv_priv*,struct sk_buff*,int*,int*) ; 
 int batadv_mcast_forw_rtr_count (struct batadv_priv*,int) ; 
 struct batadv_orig_node* batadv_mcast_forw_rtr_node_get (struct batadv_priv*,struct ethhdr*) ; 
 struct batadv_orig_node* batadv_mcast_forw_tt_node_get (struct batadv_priv*,struct ethhdr*) ; 
 struct batadv_orig_node* batadv_mcast_forw_unsnoop_node_get (struct batadv_priv*) ; 
 int batadv_mcast_forw_want_all_ip_count (struct batadv_priv*,struct ethhdr*) ; 
 int batadv_tt_global_hash_count (struct batadv_priv*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct ethhdr* eth_hdr (struct sk_buff*) ; 

enum batadv_forw_mode
batadv_mcast_forw_mode(struct batadv_priv *bat_priv, struct sk_buff *skb,
		       struct batadv_orig_node **orig)
{
	int ret, tt_count, ip_count, unsnoop_count, total_count;
	bool is_unsnoopable = false;
	unsigned int mcast_fanout;
	struct ethhdr *ethhdr;
	int is_routable = 0;
	int rtr_count = 0;

	ret = batadv_mcast_forw_mode_check(bat_priv, skb, &is_unsnoopable,
					   &is_routable);
	if (ret == -ENOMEM)
		return BATADV_FORW_NONE;
	else if (ret < 0)
		return BATADV_FORW_ALL;

	ethhdr = eth_hdr(skb);

	tt_count = batadv_tt_global_hash_count(bat_priv, ethhdr->h_dest,
					       BATADV_NO_FLAGS);
	ip_count = batadv_mcast_forw_want_all_ip_count(bat_priv, ethhdr);
	unsnoop_count = !is_unsnoopable ? 0 :
			atomic_read(&bat_priv->mcast.num_want_all_unsnoopables);
	rtr_count = batadv_mcast_forw_rtr_count(bat_priv, is_routable);

	total_count = tt_count + ip_count + unsnoop_count + rtr_count;

	switch (total_count) {
	case 1:
		if (tt_count)
			*orig = batadv_mcast_forw_tt_node_get(bat_priv, ethhdr);
		else if (ip_count)
			*orig = batadv_mcast_forw_ip_node_get(bat_priv, ethhdr);
		else if (unsnoop_count)
			*orig = batadv_mcast_forw_unsnoop_node_get(bat_priv);
		else if (rtr_count)
			*orig = batadv_mcast_forw_rtr_node_get(bat_priv,
							       ethhdr);

		if (*orig)
			return BATADV_FORW_SINGLE;

		/* fall through */
	case 0:
		return BATADV_FORW_NONE;
	default:
		mcast_fanout = atomic_read(&bat_priv->multicast_fanout);

		if (!unsnoop_count && total_count <= mcast_fanout)
			return BATADV_FORW_SOME;
	}

	return BATADV_FORW_ALL;
}