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
struct seq_file {struct kernfs_open_file* private; } ;
struct kernfs_open_file {struct cgroup_pidlist* priv; } ;
struct cgroup_pidlist {int /*<<< orphan*/  destroy_dwork; } ;
struct TYPE_4__ {TYPE_1__* cgroup; } ;
struct TYPE_3__ {int /*<<< orphan*/  pidlist_mutex; } ;

/* Variables and functions */
 int /*<<< orphan*/  CGROUP_PIDLIST_DESTROY_DELAY ; 
 int /*<<< orphan*/  cgroup_pidlist_destroy_wq ; 
 int /*<<< orphan*/  mod_delayed_work (int /*<<< orphan*/ ,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 TYPE_2__* seq_css (struct seq_file*) ; 

__attribute__((used)) static void cgroup_pidlist_stop(struct seq_file *s, void *v)
{
	struct kernfs_open_file *of = s->private;
	struct cgroup_pidlist *l = of->priv;

	if (l)
		mod_delayed_work(cgroup_pidlist_destroy_wq, &l->destroy_dwork,
				 CGROUP_PIDLIST_DESTROY_DELAY);
	mutex_unlock(&seq_css(s)->cgroup->pidlist_mutex);
}