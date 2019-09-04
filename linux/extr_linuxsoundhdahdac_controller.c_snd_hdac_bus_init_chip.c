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
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_2__ {scalar_t__ addr; } ;
struct hdac_bus {int chip_init; TYPE_1__ posbuf; scalar_t__ use_posbuf; } ;

/* Variables and functions */
 int /*<<< orphan*/  DPLBASE ; 
 int /*<<< orphan*/  DPUBASE ; 
 int /*<<< orphan*/  azx_int_clear (struct hdac_bus*) ; 
 int /*<<< orphan*/  azx_int_enable (struct hdac_bus*) ; 
 int /*<<< orphan*/  snd_hdac_bus_init_cmd_io (struct hdac_bus*) ; 
 int /*<<< orphan*/  snd_hdac_bus_reset_link (struct hdac_bus*,int) ; 
 int /*<<< orphan*/  snd_hdac_chip_writel (struct hdac_bus*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  upper_32_bits (scalar_t__) ; 

bool snd_hdac_bus_init_chip(struct hdac_bus *bus, bool full_reset)
{
	if (bus->chip_init)
		return false;

	/* reset controller */
	snd_hdac_bus_reset_link(bus, full_reset);

	/* clear interrupts */
	azx_int_clear(bus);

	/* initialize the codec command I/O */
	snd_hdac_bus_init_cmd_io(bus);

	/* enable interrupts after CORB/RIRB buffers are initialized above */
	azx_int_enable(bus);

	/* program the position buffer */
	if (bus->use_posbuf && bus->posbuf.addr) {
		snd_hdac_chip_writel(bus, DPLBASE, (u32)bus->posbuf.addr);
		snd_hdac_chip_writel(bus, DPUBASE, upper_32_bits(bus->posbuf.addr));
	}

	bus->chip_init = true;
	return true;
}