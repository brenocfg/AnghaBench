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
struct devlink_dpipe_headers {int dummy; } ;
struct devlink {int /*<<< orphan*/  lock; struct devlink_dpipe_headers* dpipe_headers; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int devlink_dpipe_headers_register(struct devlink *devlink,
				   struct devlink_dpipe_headers *dpipe_headers)
{
	mutex_lock(&devlink->lock);
	devlink->dpipe_headers = dpipe_headers;
	mutex_unlock(&devlink->lock);
	return 0;
}