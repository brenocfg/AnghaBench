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
struct TYPE_2__ {scalar_t__ chip_init; } ;
struct hda_bus {int in_reset; TYPE_1__ core; } ;
struct azx {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  azx_init_chip (struct azx*,int) ; 
 int /*<<< orphan*/  azx_stop_chip (struct azx*) ; 
 struct azx* bus_to_azx (TYPE_1__*) ; 
 int /*<<< orphan*/  snd_hda_bus_reset_codecs (struct hda_bus*) ; 

void snd_hda_bus_reset(struct hda_bus *bus)
{
	struct azx *chip = bus_to_azx(&bus->core);

	bus->in_reset = 1;
	azx_stop_chip(chip);
	azx_init_chip(chip, true);
	if (bus->core.chip_init)
		snd_hda_bus_reset_codecs(bus);
	bus->in_reset = 0;
}