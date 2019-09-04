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
struct pids_cgroup {int /*<<< orphan*/  counter; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  atomic64_add_negative (int,int /*<<< orphan*/ *) ; 

__attribute__((used)) static void pids_cancel(struct pids_cgroup *pids, int num)
{
	/*
	 * A negative count (or overflow for that matter) is invalid,
	 * and indicates a bug in the `pids` controller proper.
	 */
	WARN_ON_ONCE(atomic64_add_negative(-num, &pids->counter));
}