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
typedef  size_t u16 ;
struct sk_buff {int dummy; } ;
struct brcmf_if {int dummy; } ;
struct brcmf_flowring_ring {size_t hash_id; int /*<<< orphan*/  skblist; } ;
struct brcmf_flowring {struct brcmf_flowring_ring** rings; TYPE_1__* hash; int /*<<< orphan*/  dev; } ;
struct brcmf_bus {int /*<<< orphan*/  drvr; } ;
struct TYPE_2__ {int /*<<< orphan*/  mac; int /*<<< orphan*/  ifidx; } ;

/* Variables and functions */
 int /*<<< orphan*/  BRCMF_FLOWRING_INVALID_IFIDX ; 
 int /*<<< orphan*/  brcmf_flowring_block (struct brcmf_flowring*,size_t,int) ; 
 int /*<<< orphan*/  brcmf_flowring_ifidx_get (struct brcmf_flowring*,size_t) ; 
 struct brcmf_if* brcmf_get_ifp (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  brcmf_txfinalize (struct brcmf_if*,struct sk_buff*,int) ; 
 struct brcmf_bus* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  eth_zero_addr (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  kfree (struct brcmf_flowring_ring*) ; 
 struct sk_buff* skb_dequeue (int /*<<< orphan*/ *) ; 

void brcmf_flowring_delete(struct brcmf_flowring *flow, u16 flowid)
{
	struct brcmf_bus *bus_if = dev_get_drvdata(flow->dev);
	struct brcmf_flowring_ring *ring;
	struct brcmf_if *ifp;
	u16 hash_idx;
	u8 ifidx;
	struct sk_buff *skb;

	ring = flow->rings[flowid];
	if (!ring)
		return;

	ifidx = brcmf_flowring_ifidx_get(flow, flowid);
	ifp = brcmf_get_ifp(bus_if->drvr, ifidx);

	brcmf_flowring_block(flow, flowid, false);
	hash_idx = ring->hash_id;
	flow->hash[hash_idx].ifidx = BRCMF_FLOWRING_INVALID_IFIDX;
	eth_zero_addr(flow->hash[hash_idx].mac);
	flow->rings[flowid] = NULL;

	skb = skb_dequeue(&ring->skblist);
	while (skb) {
		brcmf_txfinalize(ifp, skb, false);
		skb = skb_dequeue(&ring->skblist);
	}

	kfree(ring);
}