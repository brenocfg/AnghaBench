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
struct cgroup {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  cgroup_parent (struct cgroup*) ; 

__attribute__((used)) static bool cgroup_is_mixable(struct cgroup *cgrp)
{
	/*
	 * Root isn't under domain level resource control exempting it from
	 * the no-internal-process constraint, so it can serve as a thread
	 * root and a parent of resource domains at the same time.
	 */
	return !cgroup_parent(cgrp);
}