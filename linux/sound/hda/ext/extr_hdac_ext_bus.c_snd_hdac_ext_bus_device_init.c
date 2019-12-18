#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {int /*<<< orphan*/  release; } ;
struct hdac_device {TYPE_1__ dev; int /*<<< orphan*/  type; struct hdac_bus* bus; } ;
struct hdac_bus {int idx; int /*<<< orphan*/  dev; } ;
typedef  int /*<<< orphan*/  name ;

/* Variables and functions */
 int /*<<< orphan*/  HDA_DEV_ASOC ; 
 int /*<<< orphan*/  default_release ; 
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*) ; 
 int snd_hdac_device_init (struct hdac_device*,struct hdac_bus*,char*,int) ; 
 int snd_hdac_device_register (struct hdac_device*) ; 
 int /*<<< orphan*/  snd_hdac_ext_bus_device_exit (struct hdac_device*) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int,int) ; 

int snd_hdac_ext_bus_device_init(struct hdac_bus *bus, int addr,
					struct hdac_device *hdev)
{
	char name[15];
	int ret;

	hdev->bus = bus;

	snprintf(name, sizeof(name), "ehdaudio%dD%d", bus->idx, addr);

	ret  = snd_hdac_device_init(hdev, bus, name, addr);
	if (ret < 0) {
		dev_err(bus->dev, "device init failed for hdac device\n");
		return ret;
	}
	hdev->type = HDA_DEV_ASOC;
	hdev->dev.release = default_release;

	ret = snd_hdac_device_register(hdev);
	if (ret) {
		dev_err(bus->dev, "failed to register hdac device\n");
		snd_hdac_ext_bus_device_exit(hdev);
		return ret;
	}

	return 0;
}