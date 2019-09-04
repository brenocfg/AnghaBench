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
struct cgroup_subsys_state {int dummy; } ;

/* Variables and functions */
 struct cgroup_subsys_state* css_next_child (int /*<<< orphan*/ *,struct cgroup_subsys_state*) ; 

__attribute__((used)) static struct cgroup_subsys_state *
css_leftmost_descendant(struct cgroup_subsys_state *pos)
{
	struct cgroup_subsys_state *last;

	do {
		last = pos;
		pos = css_next_child(NULL, pos);
	} while (pos);

	return last;
}