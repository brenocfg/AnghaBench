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
struct musb {TYPE_2__* xceiv; int /*<<< orphan*/  otg_timer; int /*<<< orphan*/  controller; } ;
struct TYPE_4__ {TYPE_1__* otg; } ;
struct TYPE_3__ {int state; } ;

/* Variables and functions */
#define  OTG_STATE_A_PERIPHERAL 133 
#define  OTG_STATE_A_SUSPEND 132 
#define  OTG_STATE_A_WAIT_BCON 131 
#define  OTG_STATE_B_IDLE 130 
#define  OTG_STATE_B_PERIPHERAL 129 
#define  OTG_STATE_B_WAIT_ACON 128 
 int /*<<< orphan*/  TA_WAIT_BCON (struct musb*) ; 
 int /*<<< orphan*/  del_timer (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ is_host_active (struct musb*) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  musb_dbg (struct musb*,char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  musb_g_reset (struct musb*) ; 
 int /*<<< orphan*/  musb_recover_from_babble (struct musb*) ; 
 int /*<<< orphan*/  usb_otg_state_string (int) ; 

__attribute__((used)) static void musb_handle_intr_reset(struct musb *musb)
{
	if (is_host_active(musb)) {
		/*
		 * When BABBLE happens what we can depends on which
		 * platform MUSB is running, because some platforms
		 * implemented proprietary means for 'recovering' from
		 * Babble conditions. One such platform is AM335x. In
		 * most cases, however, the only thing we can do is
		 * drop the session.
		 */
		dev_err(musb->controller, "Babble\n");
		musb_recover_from_babble(musb);
	} else {
		musb_dbg(musb, "BUS RESET as %s",
			usb_otg_state_string(musb->xceiv->otg->state));
		switch (musb->xceiv->otg->state) {
		case OTG_STATE_A_SUSPEND:
			musb_g_reset(musb);
			/* FALLTHROUGH */
		case OTG_STATE_A_WAIT_BCON:	/* OPT TD.4.7-900ms */
			/* never use invalid T(a_wait_bcon) */
			musb_dbg(musb, "HNP: in %s, %d msec timeout",
				usb_otg_state_string(musb->xceiv->otg->state),
				TA_WAIT_BCON(musb));
			mod_timer(&musb->otg_timer, jiffies
				+ msecs_to_jiffies(TA_WAIT_BCON(musb)));
			break;
		case OTG_STATE_A_PERIPHERAL:
			del_timer(&musb->otg_timer);
			musb_g_reset(musb);
			break;
		case OTG_STATE_B_WAIT_ACON:
			musb_dbg(musb, "HNP: RESET (%s), to b_peripheral",
				usb_otg_state_string(musb->xceiv->otg->state));
			musb->xceiv->otg->state = OTG_STATE_B_PERIPHERAL;
			musb_g_reset(musb);
			break;
		case OTG_STATE_B_IDLE:
			musb->xceiv->otg->state = OTG_STATE_B_PERIPHERAL;
			/* FALLTHROUGH */
		case OTG_STATE_B_PERIPHERAL:
			musb_g_reset(musb);
			break;
		default:
			musb_dbg(musb, "Unhandled BUS RESET as %s",
				usb_otg_state_string(musb->xceiv->otg->state));
		}
	}
}