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
struct nvmet_ns {int buffered_io; TYPE_1__* subsys; scalar_t__ enabled; } ;
struct config_item {int dummy; } ;
typedef  size_t ssize_t ;
struct TYPE_2__ {int /*<<< orphan*/  lock; } ;

/* Variables and functions */
 size_t EINVAL ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pr_err (char*) ; 
 scalar_t__ strtobool (char const*,int*) ; 
 struct nvmet_ns* to_nvmet_ns (struct config_item*) ; 

__attribute__((used)) static ssize_t nvmet_ns_buffered_io_store(struct config_item *item,
		const char *page, size_t count)
{
	struct nvmet_ns *ns = to_nvmet_ns(item);
	bool val;

	if (strtobool(page, &val))
		return -EINVAL;

	mutex_lock(&ns->subsys->lock);
	if (ns->enabled) {
		pr_err("disable ns before setting buffered_io value.\n");
		mutex_unlock(&ns->subsys->lock);
		return -EINVAL;
	}

	ns->buffered_io = val;
	mutex_unlock(&ns->subsys->lock);
	return count;
}