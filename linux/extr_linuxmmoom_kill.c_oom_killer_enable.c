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
 int oom_killer_disabled ; 
 int /*<<< orphan*/  pr_info (char*) ; 

void oom_killer_enable(void)
{
	oom_killer_disabled = false;
	pr_info("OOM killer enabled.\n");
}