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
struct pci_slot {TYPE_1__* bus; } ;
typedef  int /*<<< orphan*/  ssize_t ;
struct TYPE_2__ {int /*<<< orphan*/  cur_bus_speed; } ;

/* Variables and functions */
 int /*<<< orphan*/  bus_speed_read (int /*<<< orphan*/ ,char*) ; 

__attribute__((used)) static ssize_t cur_speed_read_file(struct pci_slot *slot, char *buf)
{
	return bus_speed_read(slot->bus->cur_bus_speed, buf);
}