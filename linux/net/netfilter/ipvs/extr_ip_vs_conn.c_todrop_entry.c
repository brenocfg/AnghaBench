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
struct TYPE_2__ {scalar_t__ expires; } ;
struct ip_vs_conn {int /*<<< orphan*/  in_pkts; TYPE_1__ timer; scalar_t__ timeout; } ;

/* Variables and functions */
 int HZ ; 
 int atomic_read (int /*<<< orphan*/ *) ; 
 scalar_t__ jiffies ; 
 scalar_t__ time_before (scalar_t__,scalar_t__) ; 

__attribute__((used)) static inline int todrop_entry(struct ip_vs_conn *cp)
{
	/*
	 * The drop rate array needs tuning for real environments.
	 * Called from timer bh only => no locking
	 */
	static const char todrop_rate[9] = {0, 1, 2, 3, 4, 5, 6, 7, 8};
	static char todrop_counter[9] = {0};
	int i;

	/* if the conn entry hasn't lasted for 60 seconds, don't drop it.
	   This will leave enough time for normal connection to get
	   through. */
	if (time_before(cp->timeout + jiffies, cp->timer.expires + 60*HZ))
		return 0;

	/* Don't drop the entry if its number of incoming packets is not
	   located in [0, 8] */
	i = atomic_read(&cp->in_pkts);
	if (i > 8 || i < 0) return 0;

	if (!todrop_rate[i]) return 0;
	if (--todrop_counter[i] > 0) return 0;

	todrop_counter[i] = todrop_rate[i];
	return 1;
}