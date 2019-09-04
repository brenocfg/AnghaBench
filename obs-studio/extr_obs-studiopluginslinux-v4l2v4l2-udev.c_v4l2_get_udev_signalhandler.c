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
typedef  int /*<<< orphan*/  signal_handler_t ;

/* Variables and functions */
 int /*<<< orphan*/ * udev_signalhandler ; 

signal_handler_t *v4l2_get_udev_signalhandler(void)
{
	return udev_signalhandler;
}