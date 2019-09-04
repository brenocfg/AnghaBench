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
struct TYPE_2__ {struct b43legacy_dmaring* tx_ring5; struct b43legacy_dmaring* tx_ring4; struct b43legacy_dmaring* tx_ring0; struct b43legacy_dmaring* tx_ring1; struct b43legacy_dmaring* tx_ring2; struct b43legacy_dmaring* tx_ring3; } ;
struct b43legacy_wldev {TYPE_1__ dma; } ;
struct b43legacy_dmaring {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  B43legacy_WARN_ON (int) ; 

__attribute__((used)) static struct b43legacy_dmaring *priority_to_txring(
						struct b43legacy_wldev *dev,
						int queue_priority)
{
	struct b43legacy_dmaring *ring;

/*FIXME: For now we always run on TX-ring-1 */
return dev->dma.tx_ring1;

	/* 0 = highest priority */
	switch (queue_priority) {
	default:
		B43legacy_WARN_ON(1);
		/* fallthrough */
	case 0:
		ring = dev->dma.tx_ring3;
		break;
	case 1:
		ring = dev->dma.tx_ring2;
		break;
	case 2:
		ring = dev->dma.tx_ring1;
		break;
	case 3:
		ring = dev->dma.tx_ring0;
		break;
	case 4:
		ring = dev->dma.tx_ring4;
		break;
	case 5:
		ring = dev->dma.tx_ring5;
		break;
	}

	return ring;
}