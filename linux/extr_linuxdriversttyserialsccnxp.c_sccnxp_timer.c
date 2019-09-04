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
struct timer_list {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  poll_time_us; } ;
struct sccnxp_port {TYPE_1__ pdata; int /*<<< orphan*/  timer; int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 struct sccnxp_port* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 struct sccnxp_port* s ; 
 int /*<<< orphan*/  sccnxp_handle_events (struct sccnxp_port*) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  timer ; 
 scalar_t__ usecs_to_jiffies (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sccnxp_timer(struct timer_list *t)
{
	struct sccnxp_port *s = from_timer(s, t, timer);
	unsigned long flags;

	spin_lock_irqsave(&s->lock, flags);
	sccnxp_handle_events(s);
	spin_unlock_irqrestore(&s->lock, flags);

	mod_timer(&s->timer, jiffies + usecs_to_jiffies(s->pdata.poll_time_us));
}