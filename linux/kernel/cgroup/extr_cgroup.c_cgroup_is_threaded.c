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
struct cgroup {struct cgroup* dom_cgrp; } ;

/* Variables and functions */

bool cgroup_is_threaded(struct cgroup *cgrp)
{
	return cgrp->dom_cgrp != cgrp;
}