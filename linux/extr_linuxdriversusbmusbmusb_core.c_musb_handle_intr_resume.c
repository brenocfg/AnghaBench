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
typedef  int u8 ;
struct musb {int port1_status; int is_active; TYPE_2__* xceiv; int /*<<< orphan*/  int_usb; int /*<<< orphan*/  finish_resume_work; scalar_t__ rh_timer; } ;
struct TYPE_4__ {TYPE_1__* otg; } ;
struct TYPE_3__ {int state; } ;

/* Variables and functions */
 int MUSB_DEVCTL_HM ; 
 int MUSB_DEVCTL_VBUS ; 
 int MUSB_DEVCTL_VBUS_SHIFT ; 
 int /*<<< orphan*/  MUSB_DEV_MODE (struct musb*) ; 
 int /*<<< orphan*/  MUSB_INTR_DISCONNECT ; 
 int /*<<< orphan*/  MUSB_INTR_SUSPEND ; 
 int MUSB_PORT_STAT_RESUME ; 
 void* OTG_STATE_A_HOST ; 
#define  OTG_STATE_A_SUSPEND 131 
#define  OTG_STATE_B_IDLE 130 
#define  OTG_STATE_B_PERIPHERAL 129 
#define  OTG_STATE_B_WAIT_ACON 128 
 int USB_PORT_STAT_C_SUSPEND ; 
 int /*<<< orphan*/  USB_RESUME_TIMEOUT ; 
 int /*<<< orphan*/  WARNING (char*,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ jiffies ; 
 scalar_t__ msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  musb_dbg (struct musb*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  musb_g_resume (struct musb*) ; 
 int /*<<< orphan*/  musb_host_resume_root_hub (struct musb*) ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  usb_otg_state_string (int) ; 

__attribute__((used)) static void musb_handle_intr_resume(struct musb *musb, u8 devctl)
{
	musb_dbg(musb, "RESUME (%s)",
			usb_otg_state_string(musb->xceiv->otg->state));

	if (devctl & MUSB_DEVCTL_HM) {
		switch (musb->xceiv->otg->state) {
		case OTG_STATE_A_SUSPEND:
			/* remote wakeup? */
			musb->port1_status |=
					(USB_PORT_STAT_C_SUSPEND << 16)
					| MUSB_PORT_STAT_RESUME;
			musb->rh_timer = jiffies
				+ msecs_to_jiffies(USB_RESUME_TIMEOUT);
			musb->xceiv->otg->state = OTG_STATE_A_HOST;
			musb->is_active = 1;
			musb_host_resume_root_hub(musb);
			schedule_delayed_work(&musb->finish_resume_work,
				msecs_to_jiffies(USB_RESUME_TIMEOUT));
			break;
		case OTG_STATE_B_WAIT_ACON:
			musb->xceiv->otg->state = OTG_STATE_B_PERIPHERAL;
			musb->is_active = 1;
			MUSB_DEV_MODE(musb);
			break;
		default:
			WARNING("bogus %s RESUME (%s)\n",
				"host",
				usb_otg_state_string(musb->xceiv->otg->state));
		}
	} else {
		switch (musb->xceiv->otg->state) {
		case OTG_STATE_A_SUSPEND:
			/* possibly DISCONNECT is upcoming */
			musb->xceiv->otg->state = OTG_STATE_A_HOST;
			musb_host_resume_root_hub(musb);
			break;
		case OTG_STATE_B_WAIT_ACON:
		case OTG_STATE_B_PERIPHERAL:
			/* disconnect while suspended?  we may
			 * not get a disconnect irq...
			 */
			if ((devctl & MUSB_DEVCTL_VBUS)
					!= (3 << MUSB_DEVCTL_VBUS_SHIFT)
					) {
				musb->int_usb |= MUSB_INTR_DISCONNECT;
				musb->int_usb &= ~MUSB_INTR_SUSPEND;
				break;
			}
			musb_g_resume(musb);
			break;
		case OTG_STATE_B_IDLE:
			musb->int_usb &= ~MUSB_INTR_SUSPEND;
			break;
		default:
			WARNING("bogus %s RESUME (%s)\n",
				"peripheral",
				usb_otg_state_string(musb->xceiv->otg->state));
		}
	}
}