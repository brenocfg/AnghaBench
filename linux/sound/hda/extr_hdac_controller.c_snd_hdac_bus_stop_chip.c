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
struct TYPE_2__ {scalar_t__ addr; } ;
struct hdac_bus {int chip_init; TYPE_1__ posbuf; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPLBASE ; 
 int /*<<< orphan*/  DPUBASE ; 
 int /*<<< orphan*/  azx_int_clear (struct hdac_bus*) ; 
 int /*<<< orphan*/  azx_int_disable (struct hdac_bus*) ; 
 int /*<<< orphan*/  snd_hdac_bus_stop_cmd_io (struct hdac_bus*) ; 
 int /*<<< orphan*/  snd_hdac_chip_writel (struct hdac_bus*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

void snd_hdac_bus_stop_chip(struct hdac_bus *bus)
{
	if (!bus->chip_init)
		return;

	/* disable interrupts */
	azx_int_disable(bus);
	azx_int_clear(bus);

	/* disable CORB/RIRB */
	snd_hdac_bus_stop_cmd_io(bus);

	/* disable position buffer */
	if (bus->posbuf.addr) {
		snd_hdac_chip_writel(bus, DPLBASE, 0);
		snd_hdac_chip_writel(bus, DPUBASE, 0);
	}

	bus->chip_init = false;
}