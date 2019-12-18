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
struct mtpav {int num_ports; } ;

/* Variables and functions */
 int MTPAV_PIDX_ADAT ; 
 int MTPAV_PIDX_COMPUTER ; 

__attribute__((used)) static int translate_subdevice_to_hwport(struct mtpav *chip, int subdev)
{
	if (subdev < 0)
		return 0x01; /* invalid - use port 0 as default */
	else if (subdev < chip->num_ports)
		return subdev + 1; /* single mtp port */
	else if (subdev < chip->num_ports * 2)
		return subdev - chip->num_ports + 0x09; /* remote port */
	else if (subdev == chip->num_ports * 2 + MTPAV_PIDX_COMPUTER)
		return 0x11; /* computer port */
	else if (subdev == chip->num_ports + MTPAV_PIDX_ADAT)
		return 0x63;		/* ADAT */
	return 0; /* all ports */
}