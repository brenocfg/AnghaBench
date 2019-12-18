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
typedef  int /*<<< orphan*/  u64 ;
struct cgroup_subsys_state {int dummy; } ;
struct cftype {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  use_hierarchy; } ;

/* Variables and functions */
 TYPE_1__* mem_cgroup_from_css (struct cgroup_subsys_state*) ; 

__attribute__((used)) static u64 mem_cgroup_hierarchy_read(struct cgroup_subsys_state *css,
				     struct cftype *cft)
{
	return mem_cgroup_from_css(css)->use_hierarchy;
}