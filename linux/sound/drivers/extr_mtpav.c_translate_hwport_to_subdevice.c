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
 int MTPAV_PIDX_BROADCAST ; 
 int MTPAV_PIDX_COMPUTER ; 

__attribute__((used)) static int translate_hwport_to_subdevice(struct mtpav *chip, int hwport)
{
	int p;
	if (hwport <= 0x00) /* all ports */
		return chip->num_ports + MTPAV_PIDX_BROADCAST;
	else if (hwport <= 0x08) { /* single port */
		p = hwport - 1;
		if (p >= chip->num_ports)
			p = 0;
		return p;
	} else if (hwport <= 0x10) { /* remote port */
		p = hwport - 0x09 + chip->num_ports;
		if (p >= chip->num_ports * 2)
			p = chip->num_ports;
		return p;
	} else if (hwport == 0x11)  /* computer port */
		return chip->num_ports + MTPAV_PIDX_COMPUTER;
	else  /* ADAT */
		return chip->num_ports + MTPAV_PIDX_ADAT;
}