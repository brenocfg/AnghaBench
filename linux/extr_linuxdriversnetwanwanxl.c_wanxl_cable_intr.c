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
typedef  int u32 ;
struct port {int /*<<< orphan*/  dev; } ;
struct TYPE_2__ {int /*<<< orphan*/  cable; } ;

/* Variables and functions */
 int STATUS_CABLE_DCD ; 
 int STATUS_CABLE_DCE ; 
 int STATUS_CABLE_DSR ; 
#define  STATUS_CABLE_EIA530 132 
#define  STATUS_CABLE_NONE 131 
 int STATUS_CABLE_PM_SHIFT ; 
#define  STATUS_CABLE_V24 130 
#define  STATUS_CABLE_V35 129 
#define  STATUS_CABLE_X21 128 
 TYPE_1__* get_status (struct port*) ; 
 int /*<<< orphan*/  netdev_info (int /*<<< orphan*/ ,char*,char const*,char const*,char const*,char const*,char const*) ; 
 int /*<<< orphan*/  netif_carrier_off (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  netif_carrier_on (int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline void wanxl_cable_intr(struct port *port)
{
	u32 value = get_status(port)->cable;
	int valid = 1;
	const char *cable, *pm, *dte = "", *dsr = "", *dcd = "";

	switch(value & 0x7) {
	case STATUS_CABLE_V35: cable = "V.35"; break;
	case STATUS_CABLE_X21: cable = "X.21"; break;
	case STATUS_CABLE_V24: cable = "V.24"; break;
	case STATUS_CABLE_EIA530: cable = "EIA530"; break;
	case STATUS_CABLE_NONE: cable = "no"; break;
	default: cable = "invalid";
	}

	switch((value >> STATUS_CABLE_PM_SHIFT) & 0x7) {
	case STATUS_CABLE_V35: pm = "V.35"; break;
	case STATUS_CABLE_X21: pm = "X.21"; break;
	case STATUS_CABLE_V24: pm = "V.24"; break;
	case STATUS_CABLE_EIA530: pm = "EIA530"; break;
	case STATUS_CABLE_NONE: pm = "no personality"; valid = 0; break;
	default: pm = "invalid personality"; valid = 0;
	}

	if (valid) {
		if ((value & 7) == ((value >> STATUS_CABLE_PM_SHIFT) & 7)) {
			dsr = (value & STATUS_CABLE_DSR) ? ", DSR ON" :
				", DSR off";
			dcd = (value & STATUS_CABLE_DCD) ? ", carrier ON" :
				", carrier off";
		}
		dte = (value & STATUS_CABLE_DCE) ? " DCE" : " DTE";
	}
	netdev_info(port->dev, "%s%s module, %s cable%s%s\n",
		    pm, dte, cable, dsr, dcd);

	if (value & STATUS_CABLE_DCD)
		netif_carrier_on(port->dev);
	else
		netif_carrier_off(port->dev);
}