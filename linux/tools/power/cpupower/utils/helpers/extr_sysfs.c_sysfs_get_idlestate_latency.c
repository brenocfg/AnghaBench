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
 int /*<<< orphan*/  IDLESTATE_LATENCY ; 
 unsigned long sysfs_idlestate_get_one_value (unsigned int,unsigned int,int /*<<< orphan*/ ) ; 

unsigned long sysfs_get_idlestate_latency(unsigned int cpu,
					  unsigned int idlestate)
{
	return sysfs_idlestate_get_one_value(cpu, idlestate, IDLESTATE_LATENCY);
}