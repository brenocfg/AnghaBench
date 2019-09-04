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
struct hdac_device {int /*<<< orphan*/  bus; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  device_del (int /*<<< orphan*/ *) ; 
 scalar_t__ device_is_registered (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hda_widget_sysfs_exit (struct hdac_device*) ; 
 int /*<<< orphan*/  snd_hdac_bus_remove_device (int /*<<< orphan*/ ,struct hdac_device*) ; 

void snd_hdac_device_unregister(struct hdac_device *codec)
{
	if (device_is_registered(&codec->dev)) {
		hda_widget_sysfs_exit(codec);
		device_del(&codec->dev);
		snd_hdac_bus_remove_device(codec->bus, codec);
	}
}