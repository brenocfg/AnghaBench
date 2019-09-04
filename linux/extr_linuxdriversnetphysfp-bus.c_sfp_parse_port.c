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
struct TYPE_2__ {int connector; int /*<<< orphan*/  e1000_base_t; } ;
struct sfp_eeprom_id {TYPE_1__ base; } ;
struct sfp_bus {int /*<<< orphan*/  sfp_dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  FIBRE ; 
 int PORT_DA ; 
#define  PORT_FIBRE 144 
 int PORT_OTHER ; 
#define  PORT_TP 143 
#define  SFP_CONNECTOR_COPPER_PIGTAIL 142 
#define  SFP_CONNECTOR_FIBERJACK 141 
#define  SFP_CONNECTOR_HSSDC_II 140 
#define  SFP_CONNECTOR_LC 139 
#define  SFP_CONNECTOR_MPO_1X12 138 
#define  SFP_CONNECTOR_MPO_2X16 137 
#define  SFP_CONNECTOR_MT_RJ 136 
#define  SFP_CONNECTOR_MU 135 
#define  SFP_CONNECTOR_MXC_2X16 134 
#define  SFP_CONNECTOR_NOSEPARATE 133 
#define  SFP_CONNECTOR_OPTICAL_PIGTAIL 132 
#define  SFP_CONNECTOR_RJ45 131 
#define  SFP_CONNECTOR_SC 130 
#define  SFP_CONNECTOR_SG 129 
#define  SFP_CONNECTOR_UNSPEC 128 
 int /*<<< orphan*/  TP ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,int) ; 
 int /*<<< orphan*/  phylink_set (unsigned long*,int /*<<< orphan*/ ) ; 

int sfp_parse_port(struct sfp_bus *bus, const struct sfp_eeprom_id *id,
		   unsigned long *support)
{
	int port;

	/* port is the physical connector, set this from the connector field. */
	switch (id->base.connector) {
	case SFP_CONNECTOR_SC:
	case SFP_CONNECTOR_FIBERJACK:
	case SFP_CONNECTOR_LC:
	case SFP_CONNECTOR_MT_RJ:
	case SFP_CONNECTOR_MU:
	case SFP_CONNECTOR_OPTICAL_PIGTAIL:
		port = PORT_FIBRE;
		break;

	case SFP_CONNECTOR_RJ45:
		port = PORT_TP;
		break;

	case SFP_CONNECTOR_COPPER_PIGTAIL:
		port = PORT_DA;
		break;

	case SFP_CONNECTOR_UNSPEC:
		if (id->base.e1000_base_t) {
			port = PORT_TP;
			break;
		}
		/* fallthrough */
	case SFP_CONNECTOR_SG: /* guess */
	case SFP_CONNECTOR_MPO_1X12:
	case SFP_CONNECTOR_MPO_2X16:
	case SFP_CONNECTOR_HSSDC_II:
	case SFP_CONNECTOR_NOSEPARATE:
	case SFP_CONNECTOR_MXC_2X16:
		port = PORT_OTHER;
		break;
	default:
		dev_warn(bus->sfp_dev, "SFP: unknown connector id 0x%02x\n",
			 id->base.connector);
		port = PORT_OTHER;
		break;
	}

	if (support) {
		switch (port) {
		case PORT_FIBRE:
			phylink_set(support, FIBRE);
			break;

		case PORT_TP:
			phylink_set(support, TP);
			break;
		}
	}

	return port;
}