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
struct soundscape {int /*<<< orphan*/  lock; int /*<<< orphan*/  io_base; } ;

/* Variables and functions */
 int host_read_unsafe (int /*<<< orphan*/ ) ; 
 unsigned long jiffies ; 
 unsigned long msecs_to_jiffies (unsigned int) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  spin_lock_irqsave (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  spin_unlock_irqrestore (int /*<<< orphan*/ *,unsigned long) ; 
 scalar_t__ time_before (unsigned long,unsigned long) ; 

__attribute__((used)) static int obp_startup_ack(struct soundscape *s, unsigned timeout)
{
	unsigned long end_time = jiffies + msecs_to_jiffies(timeout);

	do {
		unsigned long flags;
		int x;

		spin_lock_irqsave(&s->lock, flags);
		x = host_read_unsafe(s->io_base);
		spin_unlock_irqrestore(&s->lock, flags);
		if (x == 0xfe || x == 0xff)
			return 1;

		msleep(10);
	} while (time_before(jiffies, end_time));

	return 0;
}