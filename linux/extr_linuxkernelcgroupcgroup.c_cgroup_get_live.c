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
struct cgroup {int /*<<< orphan*/  self; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON_ONCE (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  cgroup_is_dead (struct cgroup*) ; 
 int /*<<< orphan*/  css_get (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void cgroup_get_live(struct cgroup *cgrp)
{
	WARN_ON_ONCE(cgroup_is_dead(cgrp));
	css_get(&cgrp->self);
}