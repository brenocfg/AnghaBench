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
typedef  int /*<<< orphan*/  swp_entry_t ;
struct TYPE_2__ {unsigned short id; } ;

/* Variables and functions */
 TYPE_1__* lookup_swap_cgroup (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 

unsigned short lookup_swap_cgroup_id(swp_entry_t ent)
{
	return lookup_swap_cgroup(ent, NULL)->id;
}