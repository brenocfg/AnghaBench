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
 int /*<<< orphan*/  os_event_destroy (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  os_event_signal (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pthread_join (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  pthread_mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  signal_handler_destroy (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  udev_event ; 
 int /*<<< orphan*/  udev_mutex ; 
 scalar_t__ udev_refs ; 
 int /*<<< orphan*/ * udev_signalhandler ; 
 int /*<<< orphan*/  udev_thread ; 

void v4l2_unref_udev(void)
{
	pthread_mutex_lock(&udev_mutex);

	/* unref udev monitor */
	if (udev_refs && --udev_refs == 0) {
		os_event_signal(udev_event);
		pthread_join(udev_thread, NULL);
		os_event_destroy(udev_event);

		if (udev_signalhandler)
			signal_handler_destroy(udev_signalhandler);
		udev_signalhandler = NULL;
	}

	pthread_mutex_unlock(&udev_mutex);
}