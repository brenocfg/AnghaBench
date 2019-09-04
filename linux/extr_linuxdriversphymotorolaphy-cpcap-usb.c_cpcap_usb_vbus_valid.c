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
struct cpcap_phy_ddata {int /*<<< orphan*/  dev; int /*<<< orphan*/  vbus; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_err (int /*<<< orphan*/ ,char*,int) ; 
 int iio_read_channel_processed (int /*<<< orphan*/ ,int*) ; 

__attribute__((used)) static bool cpcap_usb_vbus_valid(struct cpcap_phy_ddata *ddata)
{
	int error, value = 0;

	error = iio_read_channel_processed(ddata->vbus, &value);
	if (error >= 0)
		return value > 3900 ? true : false;

	dev_err(ddata->dev, "error reading VBUS: %i\n", error);

	return false;
}