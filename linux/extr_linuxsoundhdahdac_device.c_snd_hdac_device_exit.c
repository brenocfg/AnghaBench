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
struct hdac_device {int /*<<< orphan*/  chip_name; int /*<<< orphan*/  vendor_name; int /*<<< orphan*/  bus; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  pm_runtime_put_noidle (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  snd_hdac_bus_remove_device (int /*<<< orphan*/ ,struct hdac_device*) ; 

void snd_hdac_device_exit(struct hdac_device *codec)
{
	pm_runtime_put_noidle(&codec->dev);
	snd_hdac_bus_remove_device(codec->bus, codec);
	kfree(codec->vendor_name);
	kfree(codec->chip_name);
}