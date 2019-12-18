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
struct devlink_health_reporter {scalar_t__ dump_fmsg; int /*<<< orphan*/  dump_lock; int /*<<< orphan*/  refcount; TYPE_1__* devlink; int /*<<< orphan*/  list; } ;
struct TYPE_2__ {int /*<<< orphan*/  reporters_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  devlink_fmsg_free (scalar_t__) ; 
 int /*<<< orphan*/  kfree (struct devlink_health_reporter*) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  msleep (int) ; 
 int /*<<< orphan*/  mutex_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int refcount_read (int /*<<< orphan*/ *) ; 

void
devlink_health_reporter_destroy(struct devlink_health_reporter *reporter)
{
	mutex_lock(&reporter->devlink->reporters_lock);
	list_del(&reporter->list);
	mutex_unlock(&reporter->devlink->reporters_lock);
	while (refcount_read(&reporter->refcount) > 1)
		msleep(100);
	mutex_destroy(&reporter->dump_lock);
	if (reporter->dump_fmsg)
		devlink_fmsg_free(reporter->dump_fmsg);
	kfree(reporter);
}