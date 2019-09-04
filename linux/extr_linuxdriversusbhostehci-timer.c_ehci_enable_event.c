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
struct ehci_hcd {int enabled_hrtimer_events; unsigned int next_hrtimer_event; int /*<<< orphan*/  hrtimer; int /*<<< orphan*/ * hr_timeouts; } ;
typedef  int /*<<< orphan*/  ktime_t ;

/* Variables and functions */
 int /*<<< orphan*/  HRTIMER_MODE_ABS ; 
 int /*<<< orphan*/  NSEC_PER_MSEC ; 
 int /*<<< orphan*/ * event_delays_ns ; 
 int /*<<< orphan*/  hrtimer_start_range_ns (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ktime_add (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  ktime_get () ; 

__attribute__((used)) static void ehci_enable_event(struct ehci_hcd *ehci, unsigned event,
		bool resched)
{
	ktime_t		*timeout = &ehci->hr_timeouts[event];

	if (resched)
		*timeout = ktime_add(ktime_get(), event_delays_ns[event]);
	ehci->enabled_hrtimer_events |= (1 << event);

	/* Track only the lowest-numbered pending event */
	if (event < ehci->next_hrtimer_event) {
		ehci->next_hrtimer_event = event;
		hrtimer_start_range_ns(&ehci->hrtimer, *timeout,
				NSEC_PER_MSEC, HRTIMER_MODE_ABS);
	}
}