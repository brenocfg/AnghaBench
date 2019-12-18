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
typedef  int /*<<< orphan*/  u64 ;
struct posix_cputimers {struct posix_cputimer_base* bases; } ;
struct posix_cputimer_base {int /*<<< orphan*/  tqhead; int /*<<< orphan*/  nextevt; } ;
struct list_head {int dummy; } ;

/* Variables and functions */
 int CPUCLOCK_MAX ; 
 int /*<<< orphan*/  collect_timerqueue (int /*<<< orphan*/ *,struct list_head*,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void collect_posix_cputimers(struct posix_cputimers *pct, u64 *samples,
				    struct list_head *firing)
{
	struct posix_cputimer_base *base = pct->bases;
	int i;

	for (i = 0; i < CPUCLOCK_MAX; i++, base++) {
		base->nextevt = collect_timerqueue(&base->tqhead, firing,
						    samples[i]);
	}
}