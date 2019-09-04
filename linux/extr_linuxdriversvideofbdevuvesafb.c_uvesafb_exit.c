#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int /*<<< orphan*/  flags; } ;
struct uvesafb_ktask {TYPE_1__ t; } ;
struct TYPE_5__ {int /*<<< orphan*/  driver; } ;

/* Variables and functions */
 int /*<<< orphan*/  TF_EXIT ; 
 int /*<<< orphan*/  cn_del_callback (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  driver_attr_v86d ; 
 int /*<<< orphan*/  driver_remove_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  platform_device_unregister (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  platform_driver_unregister (TYPE_2__*) ; 
 int /*<<< orphan*/  uvesafb_cn_id ; 
 int /*<<< orphan*/  uvesafb_device ; 
 TYPE_2__ uvesafb_driver ; 
 int /*<<< orphan*/  uvesafb_exec (struct uvesafb_ktask*) ; 
 int /*<<< orphan*/  uvesafb_free (struct uvesafb_ktask*) ; 
 struct uvesafb_ktask* uvesafb_prep () ; 
 scalar_t__ v86d_started ; 

__attribute__((used)) static void uvesafb_exit(void)
{
	struct uvesafb_ktask *task;

	if (v86d_started) {
		task = uvesafb_prep();
		if (task) {
			task->t.flags = TF_EXIT;
			uvesafb_exec(task);
			uvesafb_free(task);
		}
	}

	cn_del_callback(&uvesafb_cn_id);
	driver_remove_file(&uvesafb_driver.driver, &driver_attr_v86d);
	platform_device_unregister(uvesafb_device);
	platform_driver_unregister(&uvesafb_driver);
}