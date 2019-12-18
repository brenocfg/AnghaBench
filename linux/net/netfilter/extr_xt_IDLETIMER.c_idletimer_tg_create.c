#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_9__   TYPE_4__ ;
typedef  struct TYPE_8__   TYPE_2__ ;
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
struct idletimer_tg_info {int timeout; TYPE_4__* timer; int /*<<< orphan*/  label; } ;
struct TYPE_8__ {int mode; TYPE_4__* name; } ;
struct TYPE_7__ {TYPE_2__ attr; int /*<<< orphan*/  show; } ;
struct TYPE_9__ {int refcnt; TYPE_1__ attr; int /*<<< orphan*/  timer; int /*<<< orphan*/  work; int /*<<< orphan*/  entry; } ;

/* Variables and functions */
 int ENOMEM ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  INIT_WORK (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int idletimer_check_sysfs_name (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  idletimer_tg_expired ; 
 int /*<<< orphan*/  idletimer_tg_kobj ; 
 int /*<<< orphan*/  idletimer_tg_list ; 
 int /*<<< orphan*/  idletimer_tg_show ; 
 int /*<<< orphan*/  idletimer_tg_work ; 
 scalar_t__ jiffies ; 
 int /*<<< orphan*/  kfree (TYPE_4__*) ; 
 TYPE_4__* kmalloc (int,int /*<<< orphan*/ ) ; 
 TYPE_4__* kstrdup (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  list_add (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mod_timer (int /*<<< orphan*/ *,scalar_t__) ; 
 scalar_t__ msecs_to_jiffies (int) ; 
 int /*<<< orphan*/  pr_debug (char*) ; 
 int /*<<< orphan*/  sysfs_attr_init (TYPE_2__*) ; 
 int sysfs_create_file (int /*<<< orphan*/ ,TYPE_2__*) ; 
 int /*<<< orphan*/  timer_setup (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int idletimer_tg_create(struct idletimer_tg_info *info)
{
	int ret;

	info->timer = kmalloc(sizeof(*info->timer), GFP_KERNEL);
	if (!info->timer) {
		ret = -ENOMEM;
		goto out;
	}

	ret = idletimer_check_sysfs_name(info->label, sizeof(info->label));
	if (ret < 0)
		goto out_free_timer;

	sysfs_attr_init(&info->timer->attr.attr);
	info->timer->attr.attr.name = kstrdup(info->label, GFP_KERNEL);
	if (!info->timer->attr.attr.name) {
		ret = -ENOMEM;
		goto out_free_timer;
	}
	info->timer->attr.attr.mode = 0444;
	info->timer->attr.show = idletimer_tg_show;

	ret = sysfs_create_file(idletimer_tg_kobj, &info->timer->attr.attr);
	if (ret < 0) {
		pr_debug("couldn't add file to sysfs");
		goto out_free_attr;
	}

	list_add(&info->timer->entry, &idletimer_tg_list);

	timer_setup(&info->timer->timer, idletimer_tg_expired, 0);
	info->timer->refcnt = 1;

	INIT_WORK(&info->timer->work, idletimer_tg_work);

	mod_timer(&info->timer->timer,
		  msecs_to_jiffies(info->timeout * 1000) + jiffies);

	return 0;

out_free_attr:
	kfree(info->timer->attr.attr.name);
out_free_timer:
	kfree(info->timer);
out:
	return ret;
}