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
typedef  int /*<<< orphan*/  u_int ;
struct pcmcia_socket {scalar_t__ thread; int /*<<< orphan*/  thread_lock; int /*<<< orphan*/  thread_events; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (int /*<<< orphan*/ *,char*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  wake_up_process (scalar_t__) ; 

void pcmcia_parse_events(struct pcmcia_socket *s, u_int events)
{
	unsigned long flags;
	dev_dbg(&s->dev, "parse_events: events %08x\n", events);
	if (s->thread) {
		spin_lock_irqsave(&s->thread_lock, flags);
		s->thread_events |= events;
		spin_unlock_irqrestore(&s->thread_lock, flags);

		wake_up_process(s->thread);
	}
}