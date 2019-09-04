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
struct freezer {int state; } ;
struct cgroup_subsys_state {int dummy; } ;

/* Variables and functions */
 int CGROUP_FREEZER_ONLINE ; 
 int CGROUP_FREEZING ; 
 int CGROUP_FREEZING_PARENT ; 
 int CGROUP_FROZEN ; 
 int /*<<< orphan*/  atomic_inc (int /*<<< orphan*/ *) ; 
 struct freezer* css_freezer (struct cgroup_subsys_state*) ; 
 int /*<<< orphan*/  freezer_mutex ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 struct freezer* parent_freezer (struct freezer*) ; 
 int /*<<< orphan*/  system_freezing_cnt ; 

__attribute__((used)) static int freezer_css_online(struct cgroup_subsys_state *css)
{
	struct freezer *freezer = css_freezer(css);
	struct freezer *parent = parent_freezer(freezer);

	mutex_lock(&freezer_mutex);

	freezer->state |= CGROUP_FREEZER_ONLINE;

	if (parent && (parent->state & CGROUP_FREEZING)) {
		freezer->state |= CGROUP_FREEZING_PARENT | CGROUP_FROZEN;
		atomic_inc(&system_freezing_cnt);
	}

	mutex_unlock(&freezer_mutex);
	return 0;
}