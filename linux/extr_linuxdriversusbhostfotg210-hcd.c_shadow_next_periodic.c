#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
union fotg210_shadow {int /*<<< orphan*/ * hw_next; TYPE_2__* qh; } ;
struct fotg210_hcd {int dummy; } ;
typedef  int /*<<< orphan*/  __hc32 ;
struct TYPE_4__ {TYPE_1__* hw; } ;
struct TYPE_3__ {int /*<<< orphan*/  hw_next; } ;

/* Variables and functions */
#define  Q_TYPE_QH 128 
 int hc32_to_cpu (struct fotg210_hcd*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static __hc32 *shadow_next_periodic(struct fotg210_hcd *fotg210,
		union fotg210_shadow *periodic, __hc32 tag)
{
	switch (hc32_to_cpu(fotg210, tag)) {
	/* our fotg210_shadow.qh is actually software part */
	case Q_TYPE_QH:
		return &periodic->qh->hw->hw_next;
	/* others are hw parts */
	default:
		return periodic->hw_next;
	}
}