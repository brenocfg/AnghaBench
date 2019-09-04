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
typedef  union xhci_trb {int dummy; } xhci_trb ;
struct xhci_segment {union xhci_trb* trbs; } ;

/* Variables and functions */
 int TRBS_PER_SEGMENT ; 

__attribute__((used)) static bool last_trb_on_seg(struct xhci_segment *seg, union xhci_trb *trb)
{
	return trb == &seg->trbs[TRBS_PER_SEGMENT - 1];
}