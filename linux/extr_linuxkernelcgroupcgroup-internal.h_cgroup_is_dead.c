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
struct TYPE_2__ {int flags; } ;
struct cgroup {TYPE_1__ self; } ;

/* Variables and functions */
 int CSS_ONLINE ; 

__attribute__((used)) static inline bool cgroup_is_dead(const struct cgroup *cgrp)
{
	return !(cgrp->self.flags & CSS_ONLINE);
}