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
struct hdac_bus {int codec_mask; int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int HDA_MAX_CODECS ; 
 int /*<<< orphan*/  dev_warn (int /*<<< orphan*/ ,char*,int) ; 
 scalar_t__ probe_codec (struct hdac_bus*,int) ; 
 int /*<<< orphan*/  skl_init_chip (struct hdac_bus*,int) ; 
 int /*<<< orphan*/  snd_hdac_bus_stop_chip (struct hdac_bus*) ; 

__attribute__((used)) static void skl_codec_create(struct hdac_bus *bus)
{
	int c, max_slots;

	max_slots = HDA_MAX_CODECS;

	/* First try to probe all given codec slots */
	for (c = 0; c < max_slots; c++) {
		if ((bus->codec_mask & (1 << c))) {
			if (probe_codec(bus, c) < 0) {
				/*
				 * Some BIOSen give you wrong codec addresses
				 * that don't exist
				 */
				dev_warn(bus->dev,
					 "Codec #%d probe error; disabling it...\n", c);
				bus->codec_mask &= ~(1 << c);
				/*
				 * More badly, accessing to a non-existing
				 * codec often screws up the controller bus,
				 * and disturbs the further communications.
				 * Thus if an error occurs during probing,
				 * better to reset the controller bus to get
				 * back to the sanity state.
				 */
				snd_hdac_bus_stop_chip(bus);
				skl_init_chip(bus, true);
			}
		}
	}
}