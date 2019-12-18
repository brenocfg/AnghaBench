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
struct udev_device {int dummy; } ;
struct calldata {int dummy; } ;
typedef  enum udev_action { ____Placeholder_udev_action } udev_action ;

/* Variables and functions */
#define  UDEV_ACTION_ADDED 129 
#define  UDEV_ACTION_REMOVED 128 
 int /*<<< orphan*/  calldata_free (struct calldata*) ; 
 int /*<<< orphan*/  calldata_init (struct calldata*) ; 
 int /*<<< orphan*/  calldata_set_string (struct calldata*,char*,char const*) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  signal_handler_signal (int /*<<< orphan*/ ,char*,struct calldata*) ; 
 int udev_action_to_enum (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  udev_device_get_action (struct udev_device*) ; 
 char* udev_device_get_devnode (struct udev_device*) ; 
 int /*<<< orphan*/  udev_mutex ; 
 int /*<<< orphan*/  udev_signalhandler ; 

__attribute__((used)) static inline void udev_signal_event(struct udev_device *dev)
{
	const char *node;
	enum udev_action action;
	struct calldata data;

	pthread_mutex_lock(&udev_mutex);

	node = udev_device_get_devnode(dev);
	action = udev_action_to_enum(udev_device_get_action(dev));

	calldata_init(&data);

	calldata_set_string(&data, "device", node);

	switch (action) {
	case UDEV_ACTION_ADDED:
		signal_handler_signal(udev_signalhandler, "device_added",
				      &data);
		break;
	case UDEV_ACTION_REMOVED:
		signal_handler_signal(udev_signalhandler, "device_removed",
				      &data);
		break;
	default:
		break;
	}

	calldata_free(&data);

	pthread_mutex_unlock(&udev_mutex);
}