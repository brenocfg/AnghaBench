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
typedef  void* u32 ;
struct hdac_bus {int unsol_wp; int /*<<< orphan*/  unsol_work; void** unsol_queue; } ;

/* Variables and functions */
 int HDA_UNSOL_QUEUE_SIZE ; 
 int /*<<< orphan*/  schedule_work (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  trace_hda_unsol_event (struct hdac_bus*,void*,void*) ; 

void snd_hdac_bus_queue_event(struct hdac_bus *bus, u32 res, u32 res_ex)
{
	unsigned int wp;

	if (!bus)
		return;

	trace_hda_unsol_event(bus, res, res_ex);
	wp = (bus->unsol_wp + 1) % HDA_UNSOL_QUEUE_SIZE;
	bus->unsol_wp = wp;

	wp <<= 1;
	bus->unsol_queue[wp] = res;
	bus->unsol_queue[wp + 1] = res_ex;

	schedule_work(&bus->unsol_work);
}