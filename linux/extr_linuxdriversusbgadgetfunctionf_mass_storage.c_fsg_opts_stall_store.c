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
struct fsg_opts {int /*<<< orphan*/  lock; TYPE_1__* common; scalar_t__ refcnt; } ;
struct config_item {int dummy; } ;
typedef  int ssize_t ;
struct TYPE_2__ {int can_stall; } ;

/* Variables and functions */
 int EBUSY ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int strtobool (char const*,int*) ; 
 struct fsg_opts* to_fsg_opts (struct config_item*) ; 

__attribute__((used)) static ssize_t fsg_opts_stall_store(struct config_item *item, const char *page,
				    size_t len)
{
	struct fsg_opts *opts = to_fsg_opts(item);
	int ret;
	bool stall;

	mutex_lock(&opts->lock);

	if (opts->refcnt) {
		mutex_unlock(&opts->lock);
		return -EBUSY;
	}

	ret = strtobool(page, &stall);
	if (!ret) {
		opts->common->can_stall = stall;
		ret = len;
	}

	mutex_unlock(&opts->lock);

	return ret;
}