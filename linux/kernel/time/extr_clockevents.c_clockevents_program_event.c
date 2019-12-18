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
struct clock_event_device {int features; int (* set_next_ktime ) (scalar_t__,struct clock_event_device*) ;unsigned long long mult; unsigned long long shift; int (* set_next_event ) (unsigned long,struct clock_event_device*) ;scalar_t__ min_delta_ns; scalar_t__ max_delta_ns; scalar_t__ next_event; } ;
typedef  scalar_t__ ktime_t ;
typedef  scalar_t__ int64_t ;

/* Variables and functions */
 int CLOCK_EVT_FEAT_KTIME ; 
 int ETIME ; 
 int /*<<< orphan*/  WARN_ONCE (int,char*,int /*<<< orphan*/ ) ; 
 scalar_t__ WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  clockevent_get_state (struct clock_event_device*) ; 
 int /*<<< orphan*/  clockevent_state_oneshot (struct clock_event_device*) ; 
 scalar_t__ clockevent_state_shutdown (struct clock_event_device*) ; 
 int clockevents_program_min_delta (struct clock_event_device*) ; 
 int /*<<< orphan*/  ktime_get () ; 
 int /*<<< orphan*/  ktime_sub (scalar_t__,int /*<<< orphan*/ ) ; 
 scalar_t__ ktime_to_ns (int /*<<< orphan*/ ) ; 
 scalar_t__ max (scalar_t__,scalar_t__) ; 
 scalar_t__ min (scalar_t__,scalar_t__) ; 
 int stub1 (scalar_t__,struct clock_event_device*) ; 
 int stub2 (unsigned long,struct clock_event_device*) ; 

int clockevents_program_event(struct clock_event_device *dev, ktime_t expires,
			      bool force)
{
	unsigned long long clc;
	int64_t delta;
	int rc;

	if (WARN_ON_ONCE(expires < 0))
		return -ETIME;

	dev->next_event = expires;

	if (clockevent_state_shutdown(dev))
		return 0;

	/* We must be in ONESHOT state here */
	WARN_ONCE(!clockevent_state_oneshot(dev), "Current state: %d\n",
		  clockevent_get_state(dev));

	/* Shortcut for clockevent devices that can deal with ktime. */
	if (dev->features & CLOCK_EVT_FEAT_KTIME)
		return dev->set_next_ktime(expires, dev);

	delta = ktime_to_ns(ktime_sub(expires, ktime_get()));
	if (delta <= 0)
		return force ? clockevents_program_min_delta(dev) : -ETIME;

	delta = min(delta, (int64_t) dev->max_delta_ns);
	delta = max(delta, (int64_t) dev->min_delta_ns);

	clc = ((unsigned long long) delta * dev->mult) >> dev->shift;
	rc = dev->set_next_event((unsigned long) clc, dev);

	return (rc && force) ? clockevents_program_min_delta(dev) : rc;
}