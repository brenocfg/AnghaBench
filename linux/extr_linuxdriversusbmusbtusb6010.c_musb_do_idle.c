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
typedef  int u32 ;
struct timer_list {int dummy; } ;
struct musb {int port1_status; int /*<<< orphan*/  lock; int /*<<< orphan*/  gadget_driver; int /*<<< orphan*/  is_active; TYPE_2__* xceiv; int /*<<< orphan*/  controller; int /*<<< orphan*/  idle_timeout; int /*<<< orphan*/  a_wait_bcon; } ;
struct TYPE_4__ {TYPE_1__* otg; } ;
struct TYPE_3__ {int state; } ;

/* Variables and functions */
#define  OTG_STATE_A_IDLE 129 
#define  OTG_STATE_A_WAIT_BCON 128 
 int TUSB_PRCM_WBUS ; 
 int TUSB_PRCM_WHOSTDISCON ; 
 int TUSB_PRCM_WID ; 
 int TUSB_PRCM_WVBUS ; 
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ ,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_timer ; 
 struct musb* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 scalar_t__ is_host_active (struct musb*) ; 
 int /*<<< orphan*/  jiffies ; 
 struct musb* musb ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  time_after (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tusb_allow_idle (struct musb*,int) ; 
 int /*<<< orphan*/  tusb_musb_set_vbus (struct musb*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  usb_otg_state_string (int) ; 

__attribute__((used)) static void musb_do_idle(struct timer_list *t)
{
	struct musb	*musb = from_timer(musb, t, dev_timer);
	unsigned long	flags;

	spin_lock_irqsave(&musb->lock, flags);

	switch (musb->xceiv->otg->state) {
	case OTG_STATE_A_WAIT_BCON:
		if ((musb->a_wait_bcon != 0)
			&& (musb->idle_timeout == 0
				|| time_after(jiffies, musb->idle_timeout))) {
			dev_dbg(musb->controller, "Nothing connected %s, turning off VBUS\n",
					usb_otg_state_string(musb->xceiv->otg->state));
		}
		/* FALLTHROUGH */
	case OTG_STATE_A_IDLE:
		tusb_musb_set_vbus(musb, 0);
	default:
		break;
	}

	if (!musb->is_active) {
		u32	wakeups;

		/* wait until hub_wq handles port change status */
		if (is_host_active(musb) && (musb->port1_status >> 16))
			goto done;

		if (!musb->gadget_driver) {
			wakeups = 0;
		} else {
			wakeups = TUSB_PRCM_WHOSTDISCON
				| TUSB_PRCM_WBUS
					| TUSB_PRCM_WVBUS;
			wakeups |= TUSB_PRCM_WID;
		}
		tusb_allow_idle(musb, wakeups);
	}
done:
	spin_unlock_irqrestore(&musb->lock, flags);
}