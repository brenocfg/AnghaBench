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
typedef  int /*<<< orphan*/  u8 ;
struct sk_buff {scalar_t__ data; } ;
struct mesh_path {int flags; int /*<<< orphan*/  frame_queue; } ;
struct TYPE_2__ {int flags; } ;
struct ieee80211_tx_info {int /*<<< orphan*/  flags; TYPE_1__ control; } ;
struct ieee80211_sub_if_data {int dummy; } ;
struct ieee80211_hdr {int /*<<< orphan*/  frame_control; int /*<<< orphan*/ * addr3; } ;

/* Variables and functions */
 int ENOENT ; 
 struct ieee80211_tx_info* IEEE80211_SKB_CB (struct sk_buff*) ; 
 int IEEE80211_TX_CTRL_SKIP_MPATH_LOOKUP ; 
 int /*<<< orphan*/  IEEE80211_TX_INTFL_NEED_TXPROCESSING ; 
 scalar_t__ IS_ERR (struct mesh_path*) ; 
 scalar_t__ MESH_FRAME_QUEUE_LEN ; 
 int MESH_PATH_RESOLVING ; 
 int /*<<< orphan*/  PREQ_Q_F_START ; 
 int PTR_ERR (struct mesh_path*) ; 
 scalar_t__ ieee80211_is_qos_nullfunc (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ieee80211_set_qos_hdr (struct ieee80211_sub_if_data*,struct sk_buff*) ; 
 int /*<<< orphan*/  mesh_nexthop_lookup (struct ieee80211_sub_if_data*,struct sk_buff*) ; 
 struct mesh_path* mesh_path_add (struct ieee80211_sub_if_data*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mesh_path_discard_frame (struct ieee80211_sub_if_data*,struct sk_buff*) ; 
 struct mesh_path* mesh_path_lookup (struct ieee80211_sub_if_data*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mesh_queue_preq (struct mesh_path*,int /*<<< orphan*/ ) ; 
 struct sk_buff* skb_dequeue (int /*<<< orphan*/ *) ; 
 scalar_t__ skb_queue_len (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  skb_queue_tail (int /*<<< orphan*/ *,struct sk_buff*) ; 

int mesh_nexthop_resolve(struct ieee80211_sub_if_data *sdata,
			 struct sk_buff *skb)
{
	struct ieee80211_hdr *hdr = (struct ieee80211_hdr *) skb->data;
	struct ieee80211_tx_info *info = IEEE80211_SKB_CB(skb);
	struct mesh_path *mpath;
	struct sk_buff *skb_to_free = NULL;
	u8 *target_addr = hdr->addr3;

	/* Nulls are only sent to peers for PS and should be pre-addressed */
	if (ieee80211_is_qos_nullfunc(hdr->frame_control))
		return 0;

	/* Allow injected packets to bypass mesh routing */
	if (info->control.flags & IEEE80211_TX_CTRL_SKIP_MPATH_LOOKUP)
		return 0;

	if (!mesh_nexthop_lookup(sdata, skb))
		return 0;

	/* no nexthop found, start resolving */
	mpath = mesh_path_lookup(sdata, target_addr);
	if (!mpath) {
		mpath = mesh_path_add(sdata, target_addr);
		if (IS_ERR(mpath)) {
			mesh_path_discard_frame(sdata, skb);
			return PTR_ERR(mpath);
		}
	}

	if (!(mpath->flags & MESH_PATH_RESOLVING))
		mesh_queue_preq(mpath, PREQ_Q_F_START);

	if (skb_queue_len(&mpath->frame_queue) >= MESH_FRAME_QUEUE_LEN)
		skb_to_free = skb_dequeue(&mpath->frame_queue);

	info->flags |= IEEE80211_TX_INTFL_NEED_TXPROCESSING;
	ieee80211_set_qos_hdr(sdata, skb);
	skb_queue_tail(&mpath->frame_queue, skb);
	if (skb_to_free)
		mesh_path_discard_frame(sdata, skb_to_free);

	return -ENOENT;
}