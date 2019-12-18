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
typedef  scalar_t__ u32 ;
struct devlink {int /*<<< orphan*/  lock; scalar_t__ snapshot_id; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

u32 devlink_region_shapshot_id_get(struct devlink *devlink)
{
	u32 id;

	mutex_lock(&devlink->lock);
	id = ++devlink->snapshot_id;
	mutex_unlock(&devlink->lock);

	return id;
}