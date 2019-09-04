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
struct fotg210_hcd {scalar_t__ rh_state; int command; scalar_t__ periodic_count; scalar_t__ PSS_poll_count; TYPE_1__* regs; } ;
struct TYPE_2__ {int /*<<< orphan*/  status; } ;

/* Variables and functions */
 int CMD_PSE ; 
 int /*<<< orphan*/  FOTG210_HRTIMER_DISABLE_PERIODIC ; 
 int /*<<< orphan*/  FOTG210_HRTIMER_POLL_PSS ; 
 scalar_t__ FOTG210_RH_RUNNING ; 
 unsigned int STS_PSS ; 
 int /*<<< orphan*/  fotg210_dbg (struct fotg210_hcd*,char*,unsigned int,unsigned int) ; 
 int /*<<< orphan*/  fotg210_enable_event (struct fotg210_hcd*,int /*<<< orphan*/ ,int) ; 
 unsigned int fotg210_readl (struct fotg210_hcd*,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fotg210_set_command_bit (struct fotg210_hcd*,int) ; 

__attribute__((used)) static void fotg210_poll_PSS(struct fotg210_hcd *fotg210)
{
	unsigned actual, want;

	/* Don't do anything if the controller isn't running (e.g., died) */
	if (fotg210->rh_state != FOTG210_RH_RUNNING)
		return;

	want = (fotg210->command & CMD_PSE) ? STS_PSS : 0;
	actual = fotg210_readl(fotg210, &fotg210->regs->status) & STS_PSS;

	if (want != actual) {

		/* Poll again later, but give up after about 20 ms */
		if (fotg210->PSS_poll_count++ < 20) {
			fotg210_enable_event(fotg210, FOTG210_HRTIMER_POLL_PSS,
					true);
			return;
		}
		fotg210_dbg(fotg210, "Waited too long for the periodic schedule status (%x/%x), giving up\n",
				want, actual);
	}
	fotg210->PSS_poll_count = 0;

	/* The status is up-to-date; restart or stop the schedule as needed */
	if (want == 0) {	/* Stopped */
		if (fotg210->periodic_count > 0)
			fotg210_set_command_bit(fotg210, CMD_PSE);

	} else {		/* Running */
		if (fotg210->periodic_count == 0) {

			/* Turn off the schedule after a while */
			fotg210_enable_event(fotg210,
					FOTG210_HRTIMER_DISABLE_PERIODIC,
					true);
		}
	}
}