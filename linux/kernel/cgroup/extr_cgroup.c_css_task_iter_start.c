#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct css_task_iter {unsigned int flags; int /*<<< orphan*/ * cset_pos; int /*<<< orphan*/ * cset_head; TYPE_1__* ss; } ;
struct cgroup_subsys_state {TYPE_2__* cgroup; TYPE_1__* ss; } ;
struct TYPE_4__ {int /*<<< orphan*/  cset_links; int /*<<< orphan*/ * e_csets; } ;
struct TYPE_3__ {size_t id; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
 int /*<<< orphan*/  css_set_lock ; 
 int /*<<< orphan*/  css_task_iter_advance (struct css_task_iter*) ; 
 int /*<<< orphan*/  memset (struct css_task_iter*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  spin_lock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_irq (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  use_task_css_set_links ; 

void css_task_iter_start(struct cgroup_subsys_state *css, unsigned int flags,
			 struct css_task_iter *it)
{
	/* no one should try to iterate before mounting cgroups */
	WARN_ON_ONCE(!use_task_css_set_links);

	memset(it, 0, sizeof(*it));

	spin_lock_irq(&css_set_lock);

	it->ss = css->ss;
	it->flags = flags;

	if (it->ss)
		it->cset_pos = &css->cgroup->e_csets[css->ss->id];
	else
		it->cset_pos = &css->cgroup->cset_links;

	it->cset_head = it->cset_pos;

	css_task_iter_advance(it);

	spin_unlock_irq(&css_set_lock);
}