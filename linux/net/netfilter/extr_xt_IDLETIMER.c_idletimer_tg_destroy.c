#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct xt_tgdtor_param {struct idletimer_tg_info* targinfo; } ;
struct idletimer_tg_info {TYPE_3__* timer; int /*<<< orphan*/  label; } ;
struct TYPE_5__ {TYPE_3__* name; } ;
struct TYPE_4__ {TYPE_2__ attr; } ;
struct TYPE_6__ {scalar_t__ refcnt; TYPE_1__ attr; int /*<<< orphan*/  work; int /*<<< orphan*/  timer; int /*<<< orphan*/  entry; } ;

/* Variables and functions */
 int /*<<< orphan*/  cancel_work_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  del_timer_sync (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  idletimer_tg_kobj ; 
 int /*<<< orphan*/  kfree (TYPE_3__*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_mutex ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,...) ; 
 int /*<<< orphan*/  sysfs_remove_file (int /*<<< orphan*/ ,TYPE_2__*) ; 

__attribute__((used)) static void idletimer_tg_destroy(const struct xt_tgdtor_param *par)
{
	const struct idletimer_tg_info *info = par->targinfo;

	pr_debug("destroy targinfo %s\n", info->label);

	mutex_lock(&list_mutex);

	if (--info->timer->refcnt == 0) {
		pr_debug("deleting timer %s\n", info->label);

		list_del(&info->timer->entry);
		del_timer_sync(&info->timer->timer);
		cancel_work_sync(&info->timer->work);
		sysfs_remove_file(idletimer_tg_kobj, &info->timer->attr.attr);
		kfree(info->timer->attr.attr.name);
		kfree(info->timer);
	} else {
		pr_debug("decreased refcnt of timer %s to %u\n",
			 info->label, info->timer->refcnt);
	}

	mutex_unlock(&list_mutex);
}