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
struct tb_ring {int vector; scalar_t__ irq; struct tb_nhi* nhi; } ;
struct tb_nhi {TYPE_1__* pdev; int /*<<< orphan*/  msix_ida; } ;
struct TYPE_2__ {int /*<<< orphan*/  msix_enabled; } ;

/* Variables and functions */
 int /*<<< orphan*/  GFP_KERNEL ; 
 unsigned long IRQF_NO_SUSPEND ; 
 int /*<<< orphan*/  MSIX_MAX_VECS ; 
 int ida_simple_get (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ pci_irq_vector (TYPE_1__*,int) ; 
 int request_irq (int,int /*<<< orphan*/ ,unsigned long,char*,struct tb_ring*) ; 
 int /*<<< orphan*/  ring_msix ; 

__attribute__((used)) static int ring_request_msix(struct tb_ring *ring, bool no_suspend)
{
	struct tb_nhi *nhi = ring->nhi;
	unsigned long irqflags;
	int ret;

	if (!nhi->pdev->msix_enabled)
		return 0;

	ret = ida_simple_get(&nhi->msix_ida, 0, MSIX_MAX_VECS, GFP_KERNEL);
	if (ret < 0)
		return ret;

	ring->vector = ret;

	ring->irq = pci_irq_vector(ring->nhi->pdev, ring->vector);
	if (ring->irq < 0)
		return ring->irq;

	irqflags = no_suspend ? IRQF_NO_SUSPEND : 0;
	return request_irq(ring->irq, ring_msix, irqflags, "thunderbolt", ring);
}