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
struct b43legacy_pioqueue {scalar_t__ mmio_base; TYPE_1__* dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  wl; } ;

/* Variables and functions */
 scalar_t__ B43legacy_MMIO_PIO1_BASE ; 
 int /*<<< orphan*/  B43legacy_PIO_RXCTL ; 
 int /*<<< orphan*/  B43legacy_PIO_RXCTL_READY ; 
 int /*<<< orphan*/  B43legacy_PIO_RXDATA ; 
 int /*<<< orphan*/  B43legacy_WARN_ON (int) ; 
 int /*<<< orphan*/  b43legacy_pio_read (struct b43legacy_pioqueue*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b43legacy_pio_write (struct b43legacy_pioqueue*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  b43legacyerr (int /*<<< orphan*/ ,char*,char const*) ; 

__attribute__((used)) static void pio_rx_error(struct b43legacy_pioqueue *queue,
			 int clear_buffers,
			 const char *error)
{
	int i;

	b43legacyerr(queue->dev->wl, "PIO RX error: %s\n", error);
	b43legacy_pio_write(queue, B43legacy_PIO_RXCTL,
			    B43legacy_PIO_RXCTL_READY);
	if (clear_buffers) {
		B43legacy_WARN_ON(queue->mmio_base != B43legacy_MMIO_PIO1_BASE);
		for (i = 0; i < 15; i++) {
			/* Dummy read. */
			b43legacy_pio_read(queue, B43legacy_PIO_RXDATA);
		}
	}
}