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

/* Variables and functions */
 int /*<<< orphan*/  busy_clock () ; 
 int /*<<< orphan*/  current ; 
 int likely (int) ; 
 int /*<<< orphan*/  need_resched () ; 
 int /*<<< orphan*/  signal_pending (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  time_after (int /*<<< orphan*/ ,unsigned long) ; 

__attribute__((used)) static bool vhost_can_busy_poll(unsigned long endtime)
{
	return likely(!need_resched() && !time_after(busy_clock(), endtime) &&
		      !signal_pending(current));
}