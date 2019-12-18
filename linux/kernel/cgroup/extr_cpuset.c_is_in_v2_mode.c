#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_5__ {TYPE_1__* root; } ;
struct TYPE_4__ {int flags; } ;

/* Variables and functions */
 int CGRP_ROOT_CPUSET_V2_MODE ; 
 scalar_t__ cgroup_subsys_on_dfl (TYPE_2__) ; 
 TYPE_2__ cpuset_cgrp_subsys ; 

__attribute__((used)) static inline bool is_in_v2_mode(void)
{
	return cgroup_subsys_on_dfl(cpuset_cgrp_subsys) ||
	      (cpuset_cgrp_subsys.root->flags & CGRP_ROOT_CPUSET_V2_MODE);
}