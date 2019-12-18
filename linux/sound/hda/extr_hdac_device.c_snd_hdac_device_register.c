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
struct hdac_device {int /*<<< orphan*/  dev; int /*<<< orphan*/  widget_lock; } ;

/* Variables and functions */
 int device_add (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  device_del (int /*<<< orphan*/ *) ; 
 int hda_widget_sysfs_init (struct hdac_device*) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int snd_hdac_device_register(struct hdac_device *codec)
{
	int err;

	err = device_add(&codec->dev);
	if (err < 0)
		return err;
	mutex_lock(&codec->widget_lock);
	err = hda_widget_sysfs_init(codec);
	mutex_unlock(&codec->widget_lock);
	if (err < 0) {
		device_del(&codec->dev);
		return err;
	}

	return 0;
}