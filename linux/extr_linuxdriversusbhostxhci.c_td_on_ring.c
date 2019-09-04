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
struct xhci_td {struct xhci_segment* start_seg; } ;
struct xhci_segment {struct xhci_segment* next; } ;
struct xhci_ring {struct xhci_segment* first_seg; } ;

/* Variables and functions */

__attribute__((used)) static bool td_on_ring(struct xhci_td *td, struct xhci_ring *ring)
{
	struct xhci_segment *seg = ring->first_seg;

	if (!td || !td->start_seg)
		return false;
	do {
		if (seg == td->start_seg)
			return true;
		seg = seg->next;
	} while (seg && seg != ring->first_seg);

	return false;
}