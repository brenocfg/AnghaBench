#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  rcu_cpu_has_work; } ;

/* Variables and functions */
 int __this_cpu_read (int /*<<< orphan*/ ) ; 
 TYPE_1__ rcu_data ; 

__attribute__((used)) static int rcu_cpu_kthread_should_run(unsigned int cpu)
{
	return __this_cpu_read(rcu_data.rcu_cpu_has_work);
}