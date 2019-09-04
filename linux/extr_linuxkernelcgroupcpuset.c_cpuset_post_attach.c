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
 int /*<<< orphan*/  cpuset_migrate_mm_wq ; 
 int /*<<< orphan*/  flush_workqueue (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void cpuset_post_attach(void)
{
	flush_workqueue(cpuset_migrate_mm_wq);
}