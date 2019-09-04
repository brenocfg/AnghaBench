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
struct ac97_controller {int /*<<< orphan*/  adap; int /*<<< orphan*/  controllers; } ;

/* Variables and functions */
 int /*<<< orphan*/  ac97_controllers_mutex ; 
 int /*<<< orphan*/  ac97_ctrl_codecs_unregister (struct ac97_controller*) ; 
 int /*<<< orphan*/  device_unregister (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  list_del (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void ac97_del_adapter(struct ac97_controller *ac97_ctrl)
{
	mutex_lock(&ac97_controllers_mutex);
	ac97_ctrl_codecs_unregister(ac97_ctrl);
	list_del(&ac97_ctrl->controllers);
	mutex_unlock(&ac97_controllers_mutex);

	device_unregister(&ac97_ctrl->adap);
}