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
struct clock_event_device {scalar_t__ irq; int /*<<< orphan*/  cpumask; } ;

/* Variables and functions */
 scalar_t__ cpumask_equal (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cpumask_of (int) ; 
 int /*<<< orphan*/  cpumask_test_cpu (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  irq_can_set_affinity (scalar_t__) ; 

__attribute__((used)) static bool tick_check_percpu(struct clock_event_device *curdev,
			      struct clock_event_device *newdev, int cpu)
{
	if (!cpumask_test_cpu(cpu, newdev->cpumask))
		return false;
	if (cpumask_equal(newdev->cpumask, cpumask_of(cpu)))
		return true;
	/* Check if irq affinity can be set */
	if (newdev->irq >= 0 && !irq_can_set_affinity(newdev->irq))
		return false;
	/* Prefer an existing cpu local device */
	if (curdev && cpumask_equal(curdev->cpumask, cpumask_of(cpu)))
		return false;
	return true;
}