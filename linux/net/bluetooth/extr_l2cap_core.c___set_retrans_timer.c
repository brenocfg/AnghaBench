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
struct l2cap_chan {scalar_t__ retrans_timeout; int /*<<< orphan*/  retrans_timer; int /*<<< orphan*/  monitor_timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  delayed_work_pending (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  l2cap_set_timer (struct l2cap_chan*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msecs_to_jiffies (scalar_t__) ; 

__attribute__((used)) static void __set_retrans_timer(struct l2cap_chan *chan)
{
	if (!delayed_work_pending(&chan->monitor_timer) &&
	    chan->retrans_timeout) {
		l2cap_set_timer(chan, &chan->retrans_timer,
				msecs_to_jiffies(chan->retrans_timeout));
	}
}