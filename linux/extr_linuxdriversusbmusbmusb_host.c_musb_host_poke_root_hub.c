#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct musb {TYPE_1__* hcd; } ;
struct TYPE_3__ {scalar_t__ status_urb; } ;

/* Variables and functions */
 int /*<<< orphan*/  MUSB_HST_MODE (struct musb*) ; 
 int /*<<< orphan*/  usb_hcd_poll_rh_status (TYPE_1__*) ; 
 int /*<<< orphan*/  usb_hcd_resume_root_hub (TYPE_1__*) ; 

void musb_host_poke_root_hub(struct musb *musb)
{
	MUSB_HST_MODE(musb);
	if (musb->hcd->status_urb)
		usb_hcd_poll_rh_status(musb->hcd);
	else
		usb_hcd_resume_root_hub(musb->hcd);
}