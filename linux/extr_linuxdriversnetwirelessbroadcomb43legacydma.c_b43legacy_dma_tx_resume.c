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
struct TYPE_2__ {int /*<<< orphan*/  tx_ring0; int /*<<< orphan*/  tx_ring1; int /*<<< orphan*/  tx_ring2; int /*<<< orphan*/  tx_ring3; int /*<<< orphan*/  tx_ring4; int /*<<< orphan*/  tx_ring5; } ;
struct b43legacy_wldev {TYPE_1__ dma; } ;

/* Variables and functions */
 int /*<<< orphan*/  b43legacy_dma_tx_resume_ring (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b43legacy_power_saving_ctl_bits (struct b43legacy_wldev*,int,int) ; 

void b43legacy_dma_tx_resume(struct b43legacy_wldev *dev)
{
	b43legacy_dma_tx_resume_ring(dev->dma.tx_ring5);
	b43legacy_dma_tx_resume_ring(dev->dma.tx_ring4);
	b43legacy_dma_tx_resume_ring(dev->dma.tx_ring3);
	b43legacy_dma_tx_resume_ring(dev->dma.tx_ring2);
	b43legacy_dma_tx_resume_ring(dev->dma.tx_ring1);
	b43legacy_dma_tx_resume_ring(dev->dma.tx_ring0);
	b43legacy_power_saving_ctl_bits(dev, -1, -1);
}