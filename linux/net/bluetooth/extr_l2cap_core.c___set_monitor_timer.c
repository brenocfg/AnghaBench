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
struct l2cap_chan {scalar_t__ monitor_timeout; int /*<<< orphan*/  monitor_timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  __clear_retrans_timer (struct l2cap_chan*) ; 
 int /*<<< orphan*/  l2cap_set_timer (struct l2cap_chan*,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msecs_to_jiffies (scalar_t__) ; 

__attribute__((used)) static void __set_monitor_timer(struct l2cap_chan *chan)
{
	__clear_retrans_timer(chan);
	if (chan->monitor_timeout) {
		l2cap_set_timer(chan, &chan->monitor_timer,
				msecs_to_jiffies(chan->monitor_timeout));
	}
}