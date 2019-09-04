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
struct fsl_ep {TYPE_1__* udc; struct ep_queue_head* qh; } ;
struct ep_queue_head {int dummy; } ;
struct TYPE_2__ {scalar_t__ ep0_dir; struct ep_queue_head* ep_qh; } ;

/* Variables and functions */
 scalar_t__ USB_DIR_IN ; 
 scalar_t__ ep_index (struct fsl_ep*) ; 

__attribute__((used)) static inline struct ep_queue_head *get_qh_by_ep(struct fsl_ep *ep)
{
	/* we only have one ep0 structure but two queue heads */
	if (ep_index(ep) != 0)
		return ep->qh;
	else
		return &ep->udc->ep_qh[(ep->udc->ep0_dir ==
				USB_DIR_IN) ? 1 : 0];
}