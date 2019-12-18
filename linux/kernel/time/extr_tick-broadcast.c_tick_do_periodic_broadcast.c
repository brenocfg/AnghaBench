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
 int /*<<< orphan*/  cpu_online_mask ; 
 int /*<<< orphan*/  cpumask_and (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tick_broadcast_mask ; 
 int tick_do_broadcast (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  tmpmask ; 

__attribute__((used)) static bool tick_do_periodic_broadcast(void)
{
	cpumask_and(tmpmask, cpu_online_mask, tick_broadcast_mask);
	return tick_do_broadcast(tmpmask);
}