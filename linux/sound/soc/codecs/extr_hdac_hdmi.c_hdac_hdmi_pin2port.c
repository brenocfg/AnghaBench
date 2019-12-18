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
struct hdac_hdmi_priv {TYPE_1__* drv_data; } ;
struct hdac_device {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int* port_map; int port_num; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ *,char*,int) ; 
 struct hdac_hdmi_priv* hdev_to_hdmi_priv (struct hdac_device*) ; 

__attribute__((used)) static int hdac_hdmi_pin2port(void *aptr, int pin)
{
	struct hdac_device *hdev = aptr;
	struct hdac_hdmi_priv *hdmi = hdev_to_hdmi_priv(hdev);
	const int *map = hdmi->drv_data->port_map;
	int i;

	if (!hdmi->drv_data->port_num)
		return pin - 4; /* map NID 0x05 -> port #1 */

	/*
	 * looking for the pin number in the mapping table and return
	 * the index which indicate the port number
	 */
	for (i = 0; i < hdmi->drv_data->port_num; i++) {
		if (pin == map[i])
			return i + 1;
	}

	/* return -1 if pin number exceeds our expectation */
	dev_err(&hdev->dev, "Can't find the port for pin %d\n", pin);
	return -1;
}