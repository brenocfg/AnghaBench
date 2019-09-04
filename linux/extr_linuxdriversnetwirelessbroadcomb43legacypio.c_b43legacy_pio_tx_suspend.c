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
struct b43legacy_pioqueue {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  B43legacy_PIO_TXCTL ; 
 int B43legacy_PIO_TXCTL_SUSPEND ; 
 int b43legacy_pio_read (struct b43legacy_pioqueue*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b43legacy_pio_write (struct b43legacy_pioqueue*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  b43legacy_power_saving_ctl_bits (int /*<<< orphan*/ ,int,int) ; 

void b43legacy_pio_tx_suspend(struct b43legacy_pioqueue *queue)
{
	b43legacy_power_saving_ctl_bits(queue->dev, -1, 1);
	b43legacy_pio_write(queue, B43legacy_PIO_TXCTL,
			    b43legacy_pio_read(queue, B43legacy_PIO_TXCTL)
			    | B43legacy_PIO_TXCTL_SUSPEND);
}