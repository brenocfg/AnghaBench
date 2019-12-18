#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
typedef  scalar_t__ u32 ;
struct TYPE_6__ {int /*<<< orphan*/  ogm_cnt_lock; } ;
struct batadv_orig_node {TYPE_3__ bat_iv; } ;
struct TYPE_5__ {int /*<<< orphan*/  bcast_own; int /*<<< orphan*/  bcast_own_sum; } ;
struct batadv_orig_ifinfo {TYPE_2__ bat_iv; } ;
struct batadv_ogm_packet {int flags; int /*<<< orphan*/  seqno; int /*<<< orphan*/  orig; } ;
struct batadv_hard_iface {TYPE_1__* net_dev; } ;
typedef  scalar_t__ s32 ;
struct TYPE_4__ {int /*<<< orphan*/  dev_addr; } ;

/* Variables and functions */
 int BATADV_DIRECTLINK ; 
 int /*<<< orphan*/  BATADV_TQ_LOCAL_WINDOW_SIZE ; 
 int /*<<< orphan*/  batadv_compare_eth (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 struct batadv_orig_ifinfo* batadv_orig_ifinfo_get (struct batadv_orig_node*,struct batadv_hard_iface*) ; 
 int /*<<< orphan*/  batadv_orig_ifinfo_put (struct batadv_orig_ifinfo*) ; 
 int /*<<< orphan*/  batadv_set_bit (int /*<<< orphan*/ ,scalar_t__) ; 
 int /*<<< orphan*/  bitmap_weight (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ ntohl (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void batadv_iv_ogm_process_reply(struct batadv_ogm_packet *ogm_packet,
					struct batadv_hard_iface *if_incoming,
					struct batadv_orig_node *orig_node,
					u32 if_incoming_seqno)
{
	struct batadv_orig_ifinfo *orig_ifinfo;
	s32 bit_pos;
	u8 *weight;

	/* neighbor has to indicate direct link and it has to
	 * come via the corresponding interface
	 */
	if (!(ogm_packet->flags & BATADV_DIRECTLINK))
		return;

	if (!batadv_compare_eth(if_incoming->net_dev->dev_addr,
				ogm_packet->orig))
		return;

	orig_ifinfo = batadv_orig_ifinfo_get(orig_node, if_incoming);
	if (!orig_ifinfo)
		return;

	/* save packet seqno for bidirectional check */
	spin_lock_bh(&orig_node->bat_iv.ogm_cnt_lock);
	bit_pos = if_incoming_seqno - 2;
	bit_pos -= ntohl(ogm_packet->seqno);
	batadv_set_bit(orig_ifinfo->bat_iv.bcast_own, bit_pos);
	weight = &orig_ifinfo->bat_iv.bcast_own_sum;
	*weight = bitmap_weight(orig_ifinfo->bat_iv.bcast_own,
				BATADV_TQ_LOCAL_WINDOW_SIZE);
	spin_unlock_bh(&orig_node->bat_iv.ogm_cnt_lock);

	batadv_orig_ifinfo_put(orig_ifinfo);
}