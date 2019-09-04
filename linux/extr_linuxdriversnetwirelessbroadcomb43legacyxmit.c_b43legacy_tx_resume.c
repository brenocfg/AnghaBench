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
struct b43legacy_wldev {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  b43legacy_dma_tx_resume (struct b43legacy_wldev*) ; 
 int /*<<< orphan*/  b43legacy_pio_thaw_txqueues (struct b43legacy_wldev*) ; 
 scalar_t__ b43legacy_using_pio (struct b43legacy_wldev*) ; 

void b43legacy_tx_resume(struct b43legacy_wldev *dev)
{
	if (b43legacy_using_pio(dev))
		b43legacy_pio_thaw_txqueues(dev);
	else
		b43legacy_dma_tx_resume(dev);
}