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
struct mii_bus {int /*<<< orphan*/ * irq; void* priv; int /*<<< orphan*/  state; } ;

/* Variables and functions */
 size_t ALIGN (int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  GFP_KERNEL ; 
 int /*<<< orphan*/  MDIOBUS_ALLOCATED ; 
 int /*<<< orphan*/  NETDEV_ALIGN ; 
 int PHY_MAX_ADDR ; 
 int /*<<< orphan*/  PHY_POLL ; 
 struct mii_bus* kzalloc (size_t,int /*<<< orphan*/ ) ; 

struct mii_bus *mdiobus_alloc_size(size_t size)
{
	struct mii_bus *bus;
	size_t aligned_size = ALIGN(sizeof(*bus), NETDEV_ALIGN);
	size_t alloc_size;
	int i;

	/* If we alloc extra space, it should be aligned */
	if (size)
		alloc_size = aligned_size + size;
	else
		alloc_size = sizeof(*bus);

	bus = kzalloc(alloc_size, GFP_KERNEL);
	if (!bus)
		return NULL;

	bus->state = MDIOBUS_ALLOCATED;
	if (size)
		bus->priv = (void *)bus + aligned_size;

	/* Initialise the interrupts to polling */
	for (i = 0; i < PHY_MAX_ADDR; i++)
		bus->irq[i] = PHY_POLL;

	return bus;
}