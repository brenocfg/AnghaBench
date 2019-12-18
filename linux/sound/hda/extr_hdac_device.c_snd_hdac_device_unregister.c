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
struct hdac_device {int /*<<< orphan*/  bus; int /*<<< orphan*/  dev; int /*<<< orphan*/  widget_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  device_del (int /*<<< orphan*/ *) ; 
 scalar_t__ device_is_registered (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hda_widget_sysfs_exit (struct hdac_device*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_hdac_bus_remove_device (int /*<<< orphan*/ ,struct hdac_device*) ; 

void snd_hdac_device_unregister(struct hdac_device *codec)
{
	if (device_is_registered(&codec->dev)) {
		mutex_lock(&codec->widget_lock);
		hda_widget_sysfs_exit(codec);
		mutex_unlock(&codec->widget_lock);
		device_del(&codec->dev);
		snd_hdac_bus_remove_device(codec->bus, codec);
	}
}