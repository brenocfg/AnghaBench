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
struct ssb_bus {scalar_t__ bustype; TYPE_1__* host_pcmcia; } ;
struct TYPE_2__ {int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 scalar_t__ SSB_BUSTYPE_PCMCIA ; 
 int /*<<< orphan*/  dev_attr_ssb_sprom ; 
 int /*<<< orphan*/  device_remove_file (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 

void ssb_pcmcia_exit(struct ssb_bus *bus)
{
	if (bus->bustype != SSB_BUSTYPE_PCMCIA)
		return;

	device_remove_file(&bus->host_pcmcia->dev, &dev_attr_ssb_sprom);
}