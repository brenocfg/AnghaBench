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
struct cgroup_subsys_state {int flags; TYPE_1__* cgroup; struct cgroup_subsys* ss; } ;
struct cgroup_subsys {size_t id; int /*<<< orphan*/  (* css_offline ) (struct cgroup_subsys_state*) ;} ;
struct TYPE_2__ {int /*<<< orphan*/  offline_waitq; int /*<<< orphan*/ * subsys; } ;

/* Variables and functions */
 int CSS_ONLINE ; 
 int /*<<< orphan*/  RCU_INIT_POINTER (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  cgroup_mutex ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  stub1 (struct cgroup_subsys_state*) ; 
 int /*<<< orphan*/  wake_up_all (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void offline_css(struct cgroup_subsys_state *css)
{
	struct cgroup_subsys *ss = css->ss;

	lockdep_assert_held(&cgroup_mutex);

	if (!(css->flags & CSS_ONLINE))
		return;

	if (ss->css_offline)
		ss->css_offline(css);

	css->flags &= ~CSS_ONLINE;
	RCU_INIT_POINTER(css->cgroup->subsys[ss->id], NULL);

	wake_up_all(&css->cgroup->offline_waitq);
}