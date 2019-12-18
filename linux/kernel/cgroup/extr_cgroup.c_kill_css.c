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
struct cgroup_subsys_state {int flags; int /*<<< orphan*/  refcnt; } ;

/* Variables and functions */
 int CSS_DYING ; 
 int /*<<< orphan*/  cgroup_mutex ; 
 int /*<<< orphan*/  css_clear_dir (struct cgroup_subsys_state*) ; 
 int /*<<< orphan*/  css_get (struct cgroup_subsys_state*) ; 
 int /*<<< orphan*/  css_killed_ref_fn ; 
 int /*<<< orphan*/  lockdep_assert_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  percpu_ref_kill_and_confirm (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void kill_css(struct cgroup_subsys_state *css)
{
	lockdep_assert_held(&cgroup_mutex);

	if (css->flags & CSS_DYING)
		return;

	css->flags |= CSS_DYING;

	/*
	 * This must happen before css is disassociated with its cgroup.
	 * See seq_css() for details.
	 */
	css_clear_dir(css);

	/*
	 * Killing would put the base ref, but we need to keep it alive
	 * until after ->css_offline().
	 */
	css_get(css);

	/*
	 * cgroup core guarantees that, by the time ->css_offline() is
	 * invoked, no new css reference will be given out via
	 * css_tryget_online().  We can't simply call percpu_ref_kill() and
	 * proceed to offlining css's because percpu_ref_kill() doesn't
	 * guarantee that the ref is seen as killed on all CPUs on return.
	 *
	 * Use percpu_ref_kill_and_confirm() to get notifications as each
	 * css is confirmed to be seen as killed on all CPUs.
	 */
	percpu_ref_kill_and_confirm(&css->refcnt, css_killed_ref_fn);
}