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
struct mem_cgroup {int /*<<< orphan*/  kmem; } ;

/* Variables and functions */
 int /*<<< orphan*/  memcg_max_mutex ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int page_counter_set_max (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static int memcg_update_kmem_max(struct mem_cgroup *memcg,
				 unsigned long max)
{
	int ret;

	mutex_lock(&memcg_max_mutex);
	ret = page_counter_set_max(&memcg->kmem, max);
	mutex_unlock(&memcg_max_mutex);
	return ret;
}