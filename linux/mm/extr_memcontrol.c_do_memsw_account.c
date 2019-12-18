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
 int /*<<< orphan*/  cgroup_subsys_on_dfl (int /*<<< orphan*/ ) ; 
 scalar_t__ do_swap_account ; 
 int /*<<< orphan*/  memory_cgrp_subsys ; 

__attribute__((used)) static bool do_memsw_account(void)
{
	return !cgroup_subsys_on_dfl(memory_cgrp_subsys) && do_swap_account;
}