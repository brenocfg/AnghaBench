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
struct tb_ring {unsigned int hop; scalar_t__ is_tx; } ;
struct tb_nhi {unsigned int hop_count; int /*<<< orphan*/  lock; struct tb_ring** rx_rings; struct tb_ring** tx_rings; TYPE_1__* pdev; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EBUSY ; 
 int EINVAL ; 
 unsigned int RING_FIRST_USABLE_HOPID ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ *,char*,unsigned int) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int nhi_alloc_hop(struct tb_nhi *nhi, struct tb_ring *ring)
{
	int ret = 0;

	spin_lock_irq(&nhi->lock);

	if (ring->hop < 0) {
		unsigned int i;

		/*
		 * Automatically allocate HopID from the non-reserved
		 * range 8 .. hop_count - 1.
		 */
		for (i = RING_FIRST_USABLE_HOPID; i < nhi->hop_count; i++) {
			if (ring->is_tx) {
				if (!nhi->tx_rings[i]) {
					ring->hop = i;
					break;
				}
			} else {
				if (!nhi->rx_rings[i]) {
					ring->hop = i;
					break;
				}
			}
		}
	}

	if (ring->hop < 0 || ring->hop >= nhi->hop_count) {
		dev_warn(&nhi->pdev->dev, "invalid hop: %d\n", ring->hop);
		ret = -EINVAL;
		goto err_unlock;
	}
	if (ring->is_tx && nhi->tx_rings[ring->hop]) {
		dev_warn(&nhi->pdev->dev, "TX hop %d already allocated\n",
			 ring->hop);
		ret = -EBUSY;
		goto err_unlock;
	} else if (!ring->is_tx && nhi->rx_rings[ring->hop]) {
		dev_warn(&nhi->pdev->dev, "RX hop %d already allocated\n",
			 ring->hop);
		ret = -EBUSY;
		goto err_unlock;
	}

	if (ring->is_tx)
		nhi->tx_rings[ring->hop] = ring;
	else
		nhi->rx_rings[ring->hop] = ring;

err_unlock:
	spin_unlock_irq(&nhi->lock);

	return ret;
}