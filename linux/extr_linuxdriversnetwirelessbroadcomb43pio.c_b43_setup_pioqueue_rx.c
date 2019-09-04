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
struct b43_wldev {TYPE_1__* dev; } ;
struct b43_pio_rxqueue {scalar_t__ mmio_base; int /*<<< orphan*/  rev; struct b43_wldev* dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  core_rev; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  b43_dma_direct_fifo_rx (struct b43_wldev*,unsigned int,int) ; 
 scalar_t__ index_to_pioqueue_base (struct b43_wldev*,unsigned int) ; 
 struct b43_pio_rxqueue* kzalloc (int,int /*<<< orphan*/ ) ; 
 scalar_t__ pio_rxqueue_offset (struct b43_wldev*) ; 

__attribute__((used)) static struct b43_pio_rxqueue *b43_setup_pioqueue_rx(struct b43_wldev *dev,
						     unsigned int index)
{
	struct b43_pio_rxqueue *q;

	q = kzalloc(sizeof(*q), GFP_KERNEL);
	if (!q)
		return NULL;
	q->dev = dev;
	q->rev = dev->dev->core_rev;
	q->mmio_base = index_to_pioqueue_base(dev, index) +
		       pio_rxqueue_offset(dev);

	/* Enable Direct FIFO RX (PIO) on the engine. */
	b43_dma_direct_fifo_rx(dev, index, 1);

	return q;
}