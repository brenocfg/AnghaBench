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
struct timer_list {int dummy; } ;
struct rose_neigh {scalar_t__ dce_mode; } ;

/* Variables and functions */
 struct rose_neigh* from_timer (int /*<<< orphan*/ ,struct timer_list*,int /*<<< orphan*/ ) ; 
 struct rose_neigh* neigh ; 
 int /*<<< orphan*/  rose_start_t0timer (struct rose_neigh*) ; 
 int /*<<< orphan*/  rose_transmit_restart_request (struct rose_neigh*) ; 
 int /*<<< orphan*/  t0timer ; 

__attribute__((used)) static void rose_t0timer_expiry(struct timer_list *t)
{
	struct rose_neigh *neigh = from_timer(neigh, t, t0timer);

	rose_transmit_restart_request(neigh);

	neigh->dce_mode = 0;

	rose_start_t0timer(neigh);
}