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
struct mem_cgroup {int /*<<< orphan*/  memory; } ;

/* Variables and functions */
 unsigned long page_counter_read (int /*<<< orphan*/ *) ; 

unsigned long mem_cgroup_size(struct mem_cgroup *memcg)
{
	return page_counter_read(&memcg->memory);
}