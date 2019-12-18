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

/* Variables and functions */
 int /*<<< orphan*/  OS_EVENT_TYPE_MANUAL ; 
 scalar_t__ os_event_init (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 scalar_t__ pthread_create (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  signal_handler_add_array (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  signal_handler_create () ; 
 int /*<<< orphan*/  udev_event ; 
 int /*<<< orphan*/  udev_event_thread ; 
 int /*<<< orphan*/  udev_mutex ; 
 scalar_t__ udev_refs ; 
 int /*<<< orphan*/  udev_signalhandler ; 
 int /*<<< orphan*/  udev_signals ; 
 int /*<<< orphan*/  udev_thread ; 

void v4l2_init_udev(void)
{
	pthread_mutex_lock(&udev_mutex);

	/* set up udev */
	if (udev_refs == 0) {
		if (os_event_init(&udev_event, OS_EVENT_TYPE_MANUAL) != 0)
			goto fail;
		if (pthread_create(&udev_thread, NULL, udev_event_thread,
				   NULL) != 0)
			goto fail;

		udev_signalhandler = signal_handler_create();
		if (!udev_signalhandler)
			goto fail;
		signal_handler_add_array(udev_signalhandler, udev_signals);
	}
	udev_refs++;

fail:
	pthread_mutex_unlock(&udev_mutex);
}