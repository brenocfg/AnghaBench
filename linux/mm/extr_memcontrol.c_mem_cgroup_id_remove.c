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
struct TYPE_2__ {scalar_t__ id; } ;
struct mem_cgroup {TYPE_1__ id; } ;

/* Variables and functions */
 int /*<<< orphan*/  idr_remove (int /*<<< orphan*/ *,scalar_t__) ; 
 int /*<<< orphan*/  mem_cgroup_idr ; 

__attribute__((used)) static void mem_cgroup_id_remove(struct mem_cgroup *memcg)
{
	if (memcg->id.id > 0) {
		idr_remove(&mem_cgroup_idr, memcg->id.id);
		memcg->id.id = 0;
	}
}