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
struct xhci_ring {int /*<<< orphan*/  enqueue; int /*<<< orphan*/  enq_seg; } ;
struct seq_file {scalar_t__ private; } ;
typedef  int /*<<< orphan*/  dma_addr_t ;

/* Variables and functions */
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xhci_trb_virt_to_dma (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int xhci_ring_enqueue_show(struct seq_file *s, void *unused)
{
	dma_addr_t		dma;
	struct xhci_ring	*ring = *(struct xhci_ring **)s->private;

	dma = xhci_trb_virt_to_dma(ring->enq_seg, ring->enqueue);
	seq_printf(s, "%pad\n", &dma);

	return 0;
}