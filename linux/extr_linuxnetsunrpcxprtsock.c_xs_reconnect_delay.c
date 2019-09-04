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
struct TYPE_2__ {unsigned long connect_start; } ;
struct rpc_xprt {unsigned long reestablish_timeout; TYPE_1__ stat; } ;

/* Variables and functions */
 unsigned long jiffies ; 
 scalar_t__ time_after (unsigned long,unsigned long) ; 

__attribute__((used)) static unsigned long xs_reconnect_delay(const struct rpc_xprt *xprt)
{
	unsigned long start, now = jiffies;

	start = xprt->stat.connect_start + xprt->reestablish_timeout;
	if (time_after(start, now))
		return start - now;
	return 0;
}