#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {unsigned int flags; } ;
struct TYPE_5__ {TYPE_1__* nsproxy; } ;
struct TYPE_4__ {int /*<<< orphan*/ * cgroup_ns; } ;

/* Variables and functions */
 unsigned int CGRP_ROOT_NS_DELEGATE ; 
 TYPE_3__ cgrp_dfl_root ; 
 TYPE_2__* current ; 
 int /*<<< orphan*/  init_cgroup_ns ; 

__attribute__((used)) static void apply_cgroup_root_flags(unsigned int root_flags)
{
	if (current->nsproxy->cgroup_ns == &init_cgroup_ns) {
		if (root_flags & CGRP_ROOT_NS_DELEGATE)
			cgrp_dfl_root.flags |= CGRP_ROOT_NS_DELEGATE;
		else
			cgrp_dfl_root.flags &= ~CGRP_ROOT_NS_DELEGATE;
	}
}