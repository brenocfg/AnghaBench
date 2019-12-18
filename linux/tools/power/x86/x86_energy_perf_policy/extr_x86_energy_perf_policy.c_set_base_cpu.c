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

/* Variables and functions */
 int /*<<< orphan*/  ENODEV ; 
 scalar_t__ base_cpu ; 
 int /*<<< orphan*/  err (int /*<<< orphan*/ ,char*) ; 
 scalar_t__ sched_getcpu () ; 

void set_base_cpu(void)
{
	base_cpu = sched_getcpu();
	if (base_cpu < 0)
		err(-ENODEV, "No valid cpus found");
}