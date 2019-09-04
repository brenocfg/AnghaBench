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
typedef  scalar_t__ u8 ;
typedef  size_t u16 ;
struct brcmf_pub {int dummy; } ;
struct brcmf_if {int dummy; } ;
struct brcmf_flowring_ring {int blocked; scalar_t__ status; } ;
struct brcmf_flowring {int nrofrings; int /*<<< orphan*/  block_lock; int /*<<< orphan*/  dev; struct brcmf_flowring_ring** rings; } ;
struct brcmf_bus {struct brcmf_pub* drvr; } ;

/* Variables and functions */
 int /*<<< orphan*/  BRCMF_NETIF_STOP_REASON_FLOW ; 
 scalar_t__ RING_OPEN ; 
 scalar_t__ brcmf_flowring_ifidx_get (struct brcmf_flowring*,int) ; 
 struct brcmf_if* brcmf_get_ifp (struct brcmf_pub*,scalar_t__) ; 
 int /*<<< orphan*/  brcmf_txflowblock_if (struct brcmf_if*,int /*<<< orphan*/ ,int) ; 
 struct brcmf_bus* dev_get_drvdata (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static void brcmf_flowring_block(struct brcmf_flowring *flow, u16 flowid,
				 bool blocked)
{
	struct brcmf_flowring_ring *ring;
	struct brcmf_bus *bus_if;
	struct brcmf_pub *drvr;
	struct brcmf_if *ifp;
	bool currently_blocked;
	int i;
	u8 ifidx;
	unsigned long flags;

	spin_lock_irqsave(&flow->block_lock, flags);

	ring = flow->rings[flowid];
	if (ring->blocked == blocked) {
		spin_unlock_irqrestore(&flow->block_lock, flags);
		return;
	}
	ifidx = brcmf_flowring_ifidx_get(flow, flowid);

	currently_blocked = false;
	for (i = 0; i < flow->nrofrings; i++) {
		if ((flow->rings[i]) && (i != flowid)) {
			ring = flow->rings[i];
			if ((ring->status == RING_OPEN) &&
			    (brcmf_flowring_ifidx_get(flow, i) == ifidx)) {
				if (ring->blocked) {
					currently_blocked = true;
					break;
				}
			}
		}
	}
	flow->rings[flowid]->blocked = blocked;
	if (currently_blocked) {
		spin_unlock_irqrestore(&flow->block_lock, flags);
		return;
	}

	bus_if = dev_get_drvdata(flow->dev);
	drvr = bus_if->drvr;
	ifp = brcmf_get_ifp(drvr, ifidx);
	brcmf_txflowblock_if(ifp, BRCMF_NETIF_STOP_REASON_FLOW, blocked);

	spin_unlock_irqrestore(&flow->block_lock, flags);
}