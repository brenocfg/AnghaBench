#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {scalar_t__ expires; } ;

/* Variables and functions */
 int /*<<< orphan*/  add_timer (TYPE_1__*) ; 
 scalar_t__ dgnc_jiffies_from_ms (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dgnc_poll_handler ; 
 int /*<<< orphan*/  dgnc_poll_lock ; 
 int /*<<< orphan*/  dgnc_poll_tick ; 
 scalar_t__ dgnc_poll_time ; 
 TYPE_1__ dgnc_poll_timer ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  timer_setup (TYPE_1__*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int dgnc_start(void)
{
	unsigned long flags;

	/* Start the poller */
	spin_lock_irqsave(&dgnc_poll_lock, flags);
	timer_setup(&dgnc_poll_timer, dgnc_poll_handler, 0);
	dgnc_poll_time = jiffies + dgnc_jiffies_from_ms(dgnc_poll_tick);
	dgnc_poll_timer.expires = dgnc_poll_time;
	spin_unlock_irqrestore(&dgnc_poll_lock, flags);

	add_timer(&dgnc_poll_timer);

	return 0;
}