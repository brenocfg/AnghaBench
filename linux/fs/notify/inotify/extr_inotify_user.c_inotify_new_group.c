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
struct inotify_event_info {int wd; scalar_t__ name_len; scalar_t__ sync_cookie; int /*<<< orphan*/  mask; int /*<<< orphan*/  fse; } ;
struct TYPE_3__ {int /*<<< orphan*/  ucounts; int /*<<< orphan*/  idr; int /*<<< orphan*/  idr_lock; } ;
struct fsnotify_group {unsigned int max_events; TYPE_1__ inotify_data; int /*<<< orphan*/  memcg; int /*<<< orphan*/ * overflow_event; } ;
struct TYPE_4__ {int /*<<< orphan*/  mm; } ;

/* Variables and functions */
 int /*<<< orphan*/  EMFILE ; 
 int /*<<< orphan*/  ENOMEM ; 
 struct fsnotify_group* ERR_PTR (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  FS_Q_OVERFLOW ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 scalar_t__ IS_ERR (struct fsnotify_group*) ; 
 int /*<<< orphan*/  UCOUNT_INOTIFY_INSTANCES ; 
 TYPE_2__* current ; 
 int /*<<< orphan*/  current_euid () ; 
 int /*<<< orphan*/  current_user_ns () ; 
 struct fsnotify_group* fsnotify_alloc_group (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  fsnotify_destroy_group (struct fsnotify_group*) ; 
 int /*<<< orphan*/  fsnotify_init_event (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  get_mem_cgroup_from_mm (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  idr_init (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  inc_ucount (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  inotify_fsnotify_ops ; 
 struct inotify_event_info* kmalloc (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock_init (int /*<<< orphan*/ *) ; 
 scalar_t__ unlikely (int) ; 

__attribute__((used)) static struct fsnotify_group *inotify_new_group(unsigned int max_events)
{
	struct fsnotify_group *group;
	struct inotify_event_info *oevent;

	group = fsnotify_alloc_group(&inotify_fsnotify_ops);
	if (IS_ERR(group))
		return group;

	oevent = kmalloc(sizeof(struct inotify_event_info), GFP_KERNEL);
	if (unlikely(!oevent)) {
		fsnotify_destroy_group(group);
		return ERR_PTR(-ENOMEM);
	}
	group->overflow_event = &oevent->fse;
	fsnotify_init_event(group->overflow_event, NULL);
	oevent->mask = FS_Q_OVERFLOW;
	oevent->wd = -1;
	oevent->sync_cookie = 0;
	oevent->name_len = 0;

	group->max_events = max_events;
	group->memcg = get_mem_cgroup_from_mm(current->mm);

	spin_lock_init(&group->inotify_data.idr_lock);
	idr_init(&group->inotify_data.idr);
	group->inotify_data.ucounts = inc_ucount(current_user_ns(),
						 current_euid(),
						 UCOUNT_INOTIFY_INSTANCES);

	if (!group->inotify_data.ucounts) {
		fsnotify_destroy_group(group);
		return ERR_PTR(-EMFILE);
	}

	return group;
}