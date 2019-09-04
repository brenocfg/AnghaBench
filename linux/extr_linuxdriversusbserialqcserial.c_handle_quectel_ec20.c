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
struct device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_dbg (struct device*,char*) ; 

__attribute__((used)) static int handle_quectel_ec20(struct device *dev, int ifnum)
{
	int altsetting = 0;

	/*
	 * Quectel EC20 Mini PCIe LTE module layout:
	 * 0: DM/DIAG (use libqcdm from ModemManager for communication)
	 * 1: NMEA
	 * 2: AT-capable modem port
	 * 3: Modem interface
	 * 4: NDIS
	 */
	switch (ifnum) {
	case 0:
		dev_dbg(dev, "Quectel EC20 DM/DIAG interface found\n");
		break;
	case 1:
		dev_dbg(dev, "Quectel EC20 NMEA GPS interface found\n");
		break;
	case 2:
	case 3:
		dev_dbg(dev, "Quectel EC20 Modem port found\n");
		break;
	case 4:
		/* Don't claim the QMI/net interface */
		altsetting = -1;
		break;
	}

	return altsetting;
}