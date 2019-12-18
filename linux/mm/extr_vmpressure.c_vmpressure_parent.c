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
struct vmpressure {int dummy; } ;
struct mem_cgroup {int dummy; } ;
struct cgroup_subsys_state {int dummy; } ;

/* Variables and functions */
 struct mem_cgroup* mem_cgroup_from_css (struct cgroup_subsys_state*) ; 
 struct vmpressure* memcg_to_vmpressure (struct mem_cgroup*) ; 
 struct mem_cgroup* parent_mem_cgroup (struct mem_cgroup*) ; 
 struct cgroup_subsys_state* vmpressure_to_css (struct vmpressure*) ; 

__attribute__((used)) static struct vmpressure *vmpressure_parent(struct vmpressure *vmpr)
{
	struct cgroup_subsys_state *css = vmpressure_to_css(vmpr);
	struct mem_cgroup *memcg = mem_cgroup_from_css(css);

	memcg = parent_mem_cgroup(memcg);
	if (!memcg)
		return NULL;
	return memcg_to_vmpressure(memcg);
}