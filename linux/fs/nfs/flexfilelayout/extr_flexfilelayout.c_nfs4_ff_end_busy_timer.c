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
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 scalar_t__ atomic_dec_return (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  ktime_sub (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static ktime_t
nfs4_ff_end_busy_timer(struct nfs4_ff_busy_timer *timer, ktime_t now)
{
	ktime_t start;

	if (atomic_dec_return(&timer->n_ops) < 0)
		WARN_ON_ONCE(1);

	start = timer->start_time;
	timer->start_time = now;
	return ktime_sub(now, start);
}