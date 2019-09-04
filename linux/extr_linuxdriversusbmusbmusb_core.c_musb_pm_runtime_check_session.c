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
typedef  int u8 ;
struct musb {int quirk_retries; int session; int /*<<< orphan*/  controller; int /*<<< orphan*/  irq_work; int /*<<< orphan*/  flush_irq_work; int /*<<< orphan*/  mregs; } ;

/* Variables and functions */
 int /*<<< orphan*/  MUSB_DEVCTL ; 
 int MUSB_DEVCTL_FSDEV ; 
 int MUSB_DEVCTL_HR ; 
 int MUSB_DEVCTL_LSDEV ; 
 int MUSB_DEVCTL_SESSION ; 
#define  MUSB_QUIRK_A_DISCONNECT_19 129 
#define  MUSB_QUIRK_B_INVALID_VBUS_91 128 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  musb_dbg (struct musb*,char*,...) ; 
 int musb_readb (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int pm_runtime_get_sync (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_mark_last_busy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put_autosuspend (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  schedule_delayed_work (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void musb_pm_runtime_check_session(struct musb *musb)
{
	u8 devctl, s;
	int error;

	devctl = musb_readb(musb->mregs, MUSB_DEVCTL);

	/* Handle session status quirks first */
	s = MUSB_DEVCTL_FSDEV | MUSB_DEVCTL_LSDEV |
		MUSB_DEVCTL_HR;
	switch (devctl & ~s) {
	case MUSB_QUIRK_B_INVALID_VBUS_91:
		if (musb->quirk_retries && !musb->flush_irq_work) {
			musb_dbg(musb,
				 "Poll devctl on invalid vbus, assume no session");
			schedule_delayed_work(&musb->irq_work,
					      msecs_to_jiffies(1000));
			musb->quirk_retries--;
			return;
		}
		/* fall through */
	case MUSB_QUIRK_A_DISCONNECT_19:
		if (musb->quirk_retries && !musb->flush_irq_work) {
			musb_dbg(musb,
				 "Poll devctl on possible host mode disconnect");
			schedule_delayed_work(&musb->irq_work,
					      msecs_to_jiffies(1000));
			musb->quirk_retries--;
			return;
		}
		if (!musb->session)
			break;
		musb_dbg(musb, "Allow PM on possible host mode disconnect");
		pm_runtime_mark_last_busy(musb->controller);
		pm_runtime_put_autosuspend(musb->controller);
		musb->session = false;
		return;
	default:
		break;
	}

	/* No need to do anything if session has not changed */
	s = devctl & MUSB_DEVCTL_SESSION;
	if (s == musb->session)
		return;

	/* Block PM or allow PM? */
	if (s) {
		musb_dbg(musb, "Block PM on active session: %02x", devctl);
		error = pm_runtime_get_sync(musb->controller);
		if (error < 0)
			dev_err(musb->controller, "Could not enable: %i\n",
				error);
		musb->quirk_retries = 3;
	} else {
		musb_dbg(musb, "Allow PM with no session: %02x", devctl);
		pm_runtime_mark_last_busy(musb->controller);
		pm_runtime_put_autosuspend(musb->controller);
	}

	musb->session = s;
}