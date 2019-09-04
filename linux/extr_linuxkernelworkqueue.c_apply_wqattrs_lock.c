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
 int /*<<< orphan*/  get_online_cpus () ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  wq_pool_mutex ; 

__attribute__((used)) static void apply_wqattrs_lock(void)
{
	/* CPUs should stay stable across pwq creations and installations */
	get_online_cpus();
	mutex_lock(&wq_pool_mutex);
}