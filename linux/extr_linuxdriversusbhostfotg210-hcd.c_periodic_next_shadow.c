#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
union fotg210_shadow {TYPE_3__* itd; TYPE_2__* fstn; TYPE_1__* qh; } ;
struct fotg210_hcd {int dummy; } ;
typedef  int /*<<< orphan*/  __hc32 ;
struct TYPE_6__ {union fotg210_shadow itd_next; } ;
struct TYPE_5__ {union fotg210_shadow fstn_next; } ;
struct TYPE_4__ {union fotg210_shadow qh_next; } ;

/* Variables and functions */
#define  Q_TYPE_FSTN 129 
#define  Q_TYPE_QH 128 
 int hc32_to_cpu (struct fotg210_hcd*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static union fotg210_shadow *periodic_next_shadow(struct fotg210_hcd *fotg210,
		union fotg210_shadow *periodic, __hc32 tag)
{
	switch (hc32_to_cpu(fotg210, tag)) {
	case Q_TYPE_QH:
		return &periodic->qh->qh_next;
	case Q_TYPE_FSTN:
		return &periodic->fstn->fstn_next;
	default:
		return &periodic->itd->itd_next;
	}
}