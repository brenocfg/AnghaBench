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
struct tb_ring {scalar_t__ irq; scalar_t__ vector; TYPE_1__* nhi; } ;
struct TYPE_2__ {int /*<<< orphan*/  msix_ida; } ;

/* Variables and functions */
 int /*<<< orphan*/  free_irq (scalar_t__,struct tb_ring*) ; 
 int /*<<< orphan*/  ida_simple_remove (int /*<<< orphan*/ *,scalar_t__) ; 

__attribute__((used)) static void ring_release_msix(struct tb_ring *ring)
{
	if (ring->irq <= 0)
		return;

	free_irq(ring->irq, ring);
	ida_simple_remove(&ring->nhi->msix_ida, ring->vector);
	ring->vector = 0;
	ring->irq = 0;
}