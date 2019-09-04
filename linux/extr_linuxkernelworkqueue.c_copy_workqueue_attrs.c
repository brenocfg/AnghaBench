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
struct workqueue_attrs {int /*<<< orphan*/  no_numa; int /*<<< orphan*/  cpumask; int /*<<< orphan*/  nice; } ;

/* Variables and functions */
 int /*<<< orphan*/  cpumask_copy (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void copy_workqueue_attrs(struct workqueue_attrs *to,
				 const struct workqueue_attrs *from)
{
	to->nice = from->nice;
	cpumask_copy(to->cpumask, from->cpumask);
	/*
	 * Unlike hash and equality test, this function doesn't ignore
	 * ->no_numa as it is used for both pool and wq attrs.  Instead,
	 * get_unbound_pool() explicitly clears ->no_numa after copying.
	 */
	to->no_numa = from->no_numa;
}