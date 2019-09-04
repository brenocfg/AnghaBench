#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_10__   TYPE_5__ ;
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_3__ ;
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  u8 ;
struct TYPE_6__ {int /*<<< orphan*/  b_hnp_enable; } ;
struct musb {int /*<<< orphan*/  is_active; TYPE_5__* hcd; TYPE_3__* xceiv; int /*<<< orphan*/  a_wait_bcon; int /*<<< orphan*/  otg_timer; TYPE_1__ g; } ;
struct TYPE_9__ {int /*<<< orphan*/  b_hnp_enable; } ;
struct TYPE_10__ {TYPE_4__ self; } ;
struct TYPE_8__ {TYPE_2__* otg; } ;
struct TYPE_7__ {int state; } ;

/* Variables and functions */
#define  OTG_STATE_A_HOST 133 
#define  OTG_STATE_A_PERIPHERAL 132 
 int OTG_STATE_A_SUSPEND ; 
#define  OTG_STATE_A_WAIT_BCON 131 
#define  OTG_STATE_B_HOST 130 
#define  OTG_STATE_B_IDLE 129 
#define  OTG_STATE_B_PERIPHERAL 128 
 int OTG_STATE_B_WAIT_ACON ; 
 int /*<<< orphan*/  OTG_TIME_A_WAIT_BCON ; 
 int /*<<< orphan*/  OTG_TIME_B_ASE0_BRST ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  musb_dbg (struct musb*,char*,...) ; 
 int /*<<< orphan*/  musb_g_suspend (struct musb*) ; 
 int /*<<< orphan*/  musb_hnp_stop (struct musb*) ; 
 int /*<<< orphan*/  musb_host_resume_root_hub (struct musb*) ; 
 int /*<<< orphan*/  musb_platform_try_idle (struct musb*,scalar_t__) ; 
 int /*<<< orphan*/  musb_root_disconnect (struct musb*) ; 
 int /*<<< orphan*/  usb_otg_state_string (int) ; 

__attribute__((used)) static void musb_handle_intr_suspend(struct musb *musb, u8 devctl)
{
	musb_dbg(musb, "SUSPEND (%s) devctl %02x",
		usb_otg_state_string(musb->xceiv->otg->state), devctl);

	switch (musb->xceiv->otg->state) {
	case OTG_STATE_A_PERIPHERAL:
		/* We also come here if the cable is removed, since
		 * this silicon doesn't report ID-no-longer-grounded.
		 *
		 * We depend on T(a_wait_bcon) to shut us down, and
		 * hope users don't do anything dicey during this
		 * undesired detour through A_WAIT_BCON.
		 */
		musb_hnp_stop(musb);
		musb_host_resume_root_hub(musb);
		musb_root_disconnect(musb);
		musb_platform_try_idle(musb, jiffies
				+ msecs_to_jiffies(musb->a_wait_bcon
					? : OTG_TIME_A_WAIT_BCON));

		break;
	case OTG_STATE_B_IDLE:
		if (!musb->is_active)
			break;
		/* fall through */
	case OTG_STATE_B_PERIPHERAL:
		musb_g_suspend(musb);
		musb->is_active = musb->g.b_hnp_enable;
		if (musb->is_active) {
			musb->xceiv->otg->state = OTG_STATE_B_WAIT_ACON;
			musb_dbg(musb, "HNP: Setting timer for b_ase0_brst");
			mod_timer(&musb->otg_timer, jiffies
				+ msecs_to_jiffies(
						OTG_TIME_B_ASE0_BRST));
		}
		break;
	case OTG_STATE_A_WAIT_BCON:
		if (musb->a_wait_bcon != 0)
			musb_platform_try_idle(musb, jiffies
				+ msecs_to_jiffies(musb->a_wait_bcon));
		break;
	case OTG_STATE_A_HOST:
		musb->xceiv->otg->state = OTG_STATE_A_SUSPEND;
		musb->is_active = musb->hcd->self.b_hnp_enable;
		break;
	case OTG_STATE_B_HOST:
		/* Transition to B_PERIPHERAL, see 6.8.2.6 p 44 */
		musb_dbg(musb, "REVISIT: SUSPEND as B_HOST");
		break;
	default:
		/* "should not happen" */
		musb->is_active = 0;
		break;
	}
}