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
struct tee_device {int /*<<< orphan*/  mutex; int /*<<< orphan*/  c_no_users; int /*<<< orphan*/ * desc; int /*<<< orphan*/  num_users; } ;

/* Variables and functions */
 int /*<<< orphan*/  WARN_ON (int) ; 
 int /*<<< orphan*/  complete (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

void tee_device_put(struct tee_device *teedev)
{
	mutex_lock(&teedev->mutex);
	/* Shouldn't put in this state */
	if (!WARN_ON(!teedev->desc)) {
		teedev->num_users--;
		if (!teedev->num_users) {
			teedev->desc = NULL;
			complete(&teedev->c_no_users);
		}
	}
	mutex_unlock(&teedev->mutex);
}