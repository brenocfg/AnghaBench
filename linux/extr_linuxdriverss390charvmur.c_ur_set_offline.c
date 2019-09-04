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
struct ccw_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int ur_set_offline_force (struct ccw_device*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  vmur_mutex ; 

__attribute__((used)) static int ur_set_offline(struct ccw_device *cdev)
{
	int rc;

	mutex_lock(&vmur_mutex);
	rc = ur_set_offline_force(cdev, 0);
	mutex_unlock(&vmur_mutex);
	return rc;
}