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
struct nfs4_ff_busy_timer {int /*<<< orphan*/  start_time; int /*<<< orphan*/  n_ops; } ;
typedef  int /*<<< orphan*/  ktime_t ;

/* Variables and functions */
 int atomic_inc_return (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void
nfs4_ff_start_busy_timer(struct nfs4_ff_busy_timer *timer, ktime_t now)
{
	/* first IO request? */
	if (atomic_inc_return(&timer->n_ops) == 1) {
		timer->start_time = now;
	}
}