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
 int CGROUP_FREEZING ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 struct freezer* css_freezer (struct cgroup_subsys_state*) ; 
 int /*<<< orphan*/  freezer_mutex ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  system_freezing_cnt ; 

__attribute__((used)) static void freezer_css_offline(struct cgroup_subsys_state *css)
{
	struct freezer *freezer = css_freezer(css);

	mutex_lock(&freezer_mutex);

	if (freezer->state & CGROUP_FREEZING)
		atomic_dec(&system_freezing_cnt);

	freezer->state = 0;

	mutex_unlock(&freezer_mutex);
}