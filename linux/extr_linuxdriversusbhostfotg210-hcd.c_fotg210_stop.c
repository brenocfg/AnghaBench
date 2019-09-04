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
struct usb_hcd {int dummy; } ;
struct fotg210_hcd {TYPE_1__* regs; int /*<<< orphan*/  lock; int /*<<< orphan*/  hrtimer; scalar_t__ enabled_hrtimer_events; } ;
struct TYPE_2__ {int /*<<< orphan*/  status; } ;

/* Variables and functions */
 int /*<<< orphan*/  dbg_status (struct fotg210_hcd*,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  end_free_itds (struct fotg210_hcd*) ; 
 int /*<<< orphan*/  fotg210_dbg (struct fotg210_hcd*,char*) ; 
 int /*<<< orphan*/  fotg210_mem_cleanup (struct fotg210_hcd*) ; 
 int /*<<< orphan*/  fotg210_quiesce (struct fotg210_hcd*) ; 
 int /*<<< orphan*/  fotg210_readl (struct fotg210_hcd*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fotg210_reset (struct fotg210_hcd*) ; 
 int /*<<< orphan*/  fotg210_silence_controller (struct fotg210_hcd*) ; 
 struct fotg210_hcd* hcd_to_fotg210 (struct usb_hcd*) ; 
 int /*<<< orphan*/  hrtimer_cancel (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  remove_debug_files (struct fotg210_hcd*) ; 
 int /*<<< orphan*/  remove_sysfs_files (struct fotg210_hcd*) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void fotg210_stop(struct usb_hcd *hcd)
{
	struct fotg210_hcd *fotg210 = hcd_to_fotg210(hcd);

	fotg210_dbg(fotg210, "stop\n");

	/* no more interrupts ... */

	spin_lock_irq(&fotg210->lock);
	fotg210->enabled_hrtimer_events = 0;
	spin_unlock_irq(&fotg210->lock);

	fotg210_quiesce(fotg210);
	fotg210_silence_controller(fotg210);
	fotg210_reset(fotg210);

	hrtimer_cancel(&fotg210->hrtimer);
	remove_sysfs_files(fotg210);
	remove_debug_files(fotg210);

	/* root hub is shut down separately (first, when possible) */
	spin_lock_irq(&fotg210->lock);
	end_free_itds(fotg210);
	spin_unlock_irq(&fotg210->lock);
	fotg210_mem_cleanup(fotg210);

#ifdef FOTG210_STATS
	fotg210_dbg(fotg210, "irq normal %ld err %ld iaa %ld (lost %ld)\n",
			fotg210->stats.normal, fotg210->stats.error,
			fotg210->stats.iaa, fotg210->stats.lost_iaa);
	fotg210_dbg(fotg210, "complete %ld unlink %ld\n",
			fotg210->stats.complete, fotg210->stats.unlink);
#endif

	dbg_status(fotg210, "fotg210_stop completed",
			fotg210_readl(fotg210, &fotg210->regs->status));
}