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
 scalar_t__ CGROUP_SUBSYS_COUNT ; 
 int /*<<< orphan*/ * cgroup_subsys_enabled_key ; 
 int static_key_enabled (int /*<<< orphan*/ ) ; 

bool cgroup_ssid_enabled(int ssid)
{
	if (CGROUP_SUBSYS_COUNT == 0)
		return false;

	return static_key_enabled(cgroup_subsys_enabled_key[ssid]);
}