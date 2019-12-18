#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct sk_buff {scalar_t__ data; } ;
struct mesh_path {TYPE_3__* sdata; int /*<<< orphan*/  next_hop; } ;
struct ieee80211s_hdr {int flags; char* eaddr1; char* eaddr2; } ;
struct ieee80211_hdr {char* addr3; char* addr4; char* addr1; char* addr2; int /*<<< orphan*/  frame_control; } ;
struct TYPE_5__ {char* addr; } ;
struct TYPE_8__ {TYPE_1__ sta; } ;
struct TYPE_6__ {char* addr; } ;
struct TYPE_7__ {TYPE_2__ vif; } ;

/* Variables and functions */
 int ETH_ALEN ; 
 int MESH_FLAGS_AE ; 
 int MESH_FLAGS_AE_A5_A6 ; 
 int ieee80211_hdrlen (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (char*,char*,int) ; 
 int /*<<< orphan*/  memmove (scalar_t__,struct ieee80211_hdr*,int) ; 
 TYPE_4__* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 int /*<<< orphan*/  skb_push (struct sk_buff*,int) ; 

__attribute__((used)) static void prepare_for_gate(struct sk_buff *skb, char *dst_addr,
			     struct mesh_path *gate_mpath)
{
	struct ieee80211_hdr *hdr;
	struct ieee80211s_hdr *mshdr;
	int mesh_hdrlen, hdrlen;
	char *next_hop;

	hdr = (struct ieee80211_hdr *) skb->data;
	hdrlen = ieee80211_hdrlen(hdr->frame_control);
	mshdr = (struct ieee80211s_hdr *) (skb->data + hdrlen);

	if (!(mshdr->flags & MESH_FLAGS_AE)) {
		/* size of the fixed part of the mesh header */
		mesh_hdrlen = 6;

		/* make room for the two extended addresses */
		skb_push(skb, 2 * ETH_ALEN);
		memmove(skb->data, hdr, hdrlen + mesh_hdrlen);

		hdr = (struct ieee80211_hdr *) skb->data;

		/* we preserve the previous mesh header and only add
		 * the new addreses */
		mshdr = (struct ieee80211s_hdr *) (skb->data + hdrlen);
		mshdr->flags = MESH_FLAGS_AE_A5_A6;
		memcpy(mshdr->eaddr1, hdr->addr3, ETH_ALEN);
		memcpy(mshdr->eaddr2, hdr->addr4, ETH_ALEN);
	}

	/* update next hop */
	hdr = (struct ieee80211_hdr *) skb->data;
	rcu_read_lock();
	next_hop = rcu_dereference(gate_mpath->next_hop)->sta.addr;
	memcpy(hdr->addr1, next_hop, ETH_ALEN);
	rcu_read_unlock();
	memcpy(hdr->addr2, gate_mpath->sdata->vif.addr, ETH_ALEN);
	memcpy(hdr->addr3, dst_addr, ETH_ALEN);
}