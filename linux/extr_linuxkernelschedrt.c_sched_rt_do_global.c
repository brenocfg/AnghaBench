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
struct TYPE_2__ {int /*<<< orphan*/  rt_period; int /*<<< orphan*/  rt_runtime; } ;

/* Variables and functions */
 TYPE_1__ def_rt_bandwidth ; 
 int /*<<< orphan*/  global_rt_period () ; 
 int /*<<< orphan*/  global_rt_runtime () ; 
 int /*<<< orphan*/  ns_to_ktime (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void sched_rt_do_global(void)
{
	def_rt_bandwidth.rt_runtime = global_rt_runtime();
	def_rt_bandwidth.rt_period = ns_to_ktime(global_rt_period());
}