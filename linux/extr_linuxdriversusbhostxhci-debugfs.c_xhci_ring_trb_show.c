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
struct xhci_segment {struct xhci_segment* next; } ;
struct xhci_ring {int num_segs; struct xhci_segment* first_seg; } ;
struct seq_file {scalar_t__ private; } ;

/* Variables and functions */
 int /*<<< orphan*/  xhci_ring_dump_segment (struct seq_file*,struct xhci_segment*) ; 

__attribute__((used)) static int xhci_ring_trb_show(struct seq_file *s, void *unused)
{
	int			i;
	struct xhci_ring	*ring = *(struct xhci_ring **)s->private;
	struct xhci_segment	*seg = ring->first_seg;

	for (i = 0; i < ring->num_segs; i++) {
		xhci_ring_dump_segment(s, seg);
		seg = seg->next;
	}

	return 0;
}