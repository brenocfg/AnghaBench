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
 int /*<<< orphan*/  WORK_CPU_UNBOUND ; 
 int /*<<< orphan*/  fscache_object_wq ; 
 int workqueue_congested (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline bool fscache_object_congested(void)
{
	return workqueue_congested(WORK_CPU_UNBOUND, fscache_object_wq);
}