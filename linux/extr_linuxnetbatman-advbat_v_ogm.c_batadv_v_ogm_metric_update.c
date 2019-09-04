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
typedef  int /*<<< orphan*/  u32 ;
struct batadv_priv {int dummy; } ;
struct batadv_orig_node {void* last_seen; int /*<<< orphan*/  neigh_list; } ;
struct batadv_orig_ifinfo {scalar_t__ last_real_seqno; int /*<<< orphan*/  last_ttl; int /*<<< orphan*/  batman_seqno_reset; } ;
struct batadv_ogm2_packet {int /*<<< orphan*/  ttl; int /*<<< orphan*/  seqno; int /*<<< orphan*/  throughput; int /*<<< orphan*/  orig; } ;
struct batadv_neigh_node {void* last_seen; } ;
struct TYPE_2__ {scalar_t__ last_seqno; int /*<<< orphan*/  throughput; } ;
struct batadv_neigh_ifinfo {int /*<<< orphan*/  last_ttl; TYPE_1__ bat_v; } ;
struct batadv_hard_iface {int dummy; } ;
typedef  scalar_t__ s32 ;

/* Variables and functions */
 int /*<<< orphan*/  BATADV_DBG_BATMAN ; 
 int /*<<< orphan*/  BATADV_OGM_MAX_AGE ; 
 int EINVAL ; 
 int /*<<< orphan*/  batadv_dbg (int /*<<< orphan*/ ,struct batadv_priv*,char*,int /*<<< orphan*/ ,...) ; 
 struct batadv_neigh_ifinfo* batadv_neigh_ifinfo_new (struct batadv_neigh_node*,struct batadv_hard_iface*) ; 
 int /*<<< orphan*/  batadv_neigh_ifinfo_put (struct batadv_neigh_ifinfo*) ; 
 struct batadv_orig_ifinfo* batadv_orig_ifinfo_new (struct batadv_orig_node*,struct batadv_hard_iface*) ; 
 int /*<<< orphan*/  batadv_orig_ifinfo_put (struct batadv_orig_ifinfo*) ; 
 int /*<<< orphan*/  batadv_v_forward_penalty (struct batadv_priv*,struct batadv_hard_iface*,struct batadv_hard_iface*,scalar_t__) ; 
 scalar_t__ batadv_window_protected (struct batadv_priv*,scalar_t__,int /*<<< orphan*/ ,int /*<<< orphan*/ *,int*) ; 
 int /*<<< orphan*/  hlist_empty (int /*<<< orphan*/ *) ; 
 void* jiffies ; 
 scalar_t__ ntohl (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int batadv_v_ogm_metric_update(struct batadv_priv *bat_priv,
				      const struct batadv_ogm2_packet *ogm2,
				      struct batadv_orig_node *orig_node,
				      struct batadv_neigh_node *neigh_node,
				      struct batadv_hard_iface *if_incoming,
				      struct batadv_hard_iface *if_outgoing)
{
	struct batadv_orig_ifinfo *orig_ifinfo;
	struct batadv_neigh_ifinfo *neigh_ifinfo = NULL;
	bool protection_started = false;
	int ret = -EINVAL;
	u32 path_throughput;
	s32 seq_diff;

	orig_ifinfo = batadv_orig_ifinfo_new(orig_node, if_outgoing);
	if (!orig_ifinfo)
		goto out;

	seq_diff = ntohl(ogm2->seqno) - orig_ifinfo->last_real_seqno;

	if (!hlist_empty(&orig_node->neigh_list) &&
	    batadv_window_protected(bat_priv, seq_diff,
				    BATADV_OGM_MAX_AGE,
				    &orig_ifinfo->batman_seqno_reset,
				    &protection_started)) {
		batadv_dbg(BATADV_DBG_BATMAN, bat_priv,
			   "Drop packet: packet within window protection time from %pM\n",
			   ogm2->orig);
		batadv_dbg(BATADV_DBG_BATMAN, bat_priv,
			   "Last reset: %ld, %ld\n",
			   orig_ifinfo->batman_seqno_reset, jiffies);
		goto out;
	}

	/* drop packets with old seqnos, however accept the first packet after
	 * a host has been rebooted.
	 */
	if (seq_diff < 0 && !protection_started)
		goto out;

	neigh_node->last_seen = jiffies;

	orig_node->last_seen = jiffies;

	orig_ifinfo->last_real_seqno = ntohl(ogm2->seqno);
	orig_ifinfo->last_ttl = ogm2->ttl;

	neigh_ifinfo = batadv_neigh_ifinfo_new(neigh_node, if_outgoing);
	if (!neigh_ifinfo)
		goto out;

	path_throughput = batadv_v_forward_penalty(bat_priv, if_incoming,
						   if_outgoing,
						   ntohl(ogm2->throughput));
	neigh_ifinfo->bat_v.throughput = path_throughput;
	neigh_ifinfo->bat_v.last_seqno = ntohl(ogm2->seqno);
	neigh_ifinfo->last_ttl = ogm2->ttl;

	if (seq_diff > 0 || protection_started)
		ret = 1;
	else
		ret = 0;
out:
	if (orig_ifinfo)
		batadv_orig_ifinfo_put(orig_ifinfo);
	if (neigh_ifinfo)
		batadv_neigh_ifinfo_put(neigh_ifinfo);

	return ret;
}