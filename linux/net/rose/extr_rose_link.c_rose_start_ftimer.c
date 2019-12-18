#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {scalar_t__ expires; int /*<<< orphan*/  function; } ;
struct rose_neigh {TYPE_1__ ftimer; } ;

/* Variables and functions */
 int /*<<< orphan*/  add_timer (TYPE_1__*) ; 
 int /*<<< orphan*/  del_timer (TYPE_1__*) ; 
 scalar_t__ jiffies ; 
 scalar_t__ msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rose_ftimer_expiry ; 
 int /*<<< orphan*/  sysctl_rose_link_fail_timeout ; 

void rose_start_ftimer(struct rose_neigh *neigh)
{
	del_timer(&neigh->ftimer);

	neigh->ftimer.function = rose_ftimer_expiry;
	neigh->ftimer.expires  =
		jiffies + msecs_to_jiffies(sysctl_rose_link_fail_timeout);

	add_timer(&neigh->ftimer);
}