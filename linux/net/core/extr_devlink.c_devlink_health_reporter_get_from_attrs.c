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
struct nlattr {int dummy; } ;
struct devlink_health_reporter {int /*<<< orphan*/  refcount; } ;
struct devlink {int /*<<< orphan*/  reporters_lock; } ;

/* Variables and functions */
 size_t DEVLINK_ATTR_HEALTH_REPORTER_NAME ; 
 struct devlink_health_reporter* devlink_health_reporter_find_by_name (struct devlink*,char*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 char* nla_data (struct nlattr*) ; 
 int /*<<< orphan*/  refcount_inc (int /*<<< orphan*/ *) ; 

__attribute__((used)) static struct devlink_health_reporter *
devlink_health_reporter_get_from_attrs(struct devlink *devlink,
				       struct nlattr **attrs)
{
	struct devlink_health_reporter *reporter;
	char *reporter_name;

	if (!attrs[DEVLINK_ATTR_HEALTH_REPORTER_NAME])
		return NULL;

	reporter_name = nla_data(attrs[DEVLINK_ATTR_HEALTH_REPORTER_NAME]);
	mutex_lock(&devlink->reporters_lock);
	reporter = devlink_health_reporter_find_by_name(devlink, reporter_name);
	if (reporter)
		refcount_inc(&reporter->refcount);
	mutex_unlock(&devlink->reporters_lock);
	return reporter;
}