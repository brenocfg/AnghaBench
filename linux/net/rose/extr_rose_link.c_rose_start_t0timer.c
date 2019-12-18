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
struct rose_neigh {TYPE_1__ t0timer; } ;

/* Variables and functions */
 int /*<<< orphan*/  add_timer (TYPE_1__*) ; 
 int /*<<< orphan*/  del_timer (TYPE_1__*) ; 
 scalar_t__ jiffies ; 
 scalar_t__ msecs_to_jiffies (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rose_t0timer_expiry ; 
 int /*<<< orphan*/  sysctl_rose_restart_request_timeout ; 

__attribute__((used)) static void rose_start_t0timer(struct rose_neigh *neigh)
{
	del_timer(&neigh->t0timer);

	neigh->t0timer.function = rose_t0timer_expiry;
	neigh->t0timer.expires  =
		jiffies + msecs_to_jiffies(sysctl_rose_restart_request_timeout);

	add_timer(&neigh->t0timer);
}