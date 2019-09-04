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
typedef  int /*<<< orphan*/  u32 ;
struct mii_bus {int /*<<< orphan*/  mdio_lock; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  MDIO_MUTEX_NESTED ; 
 int __mdiobus_read (struct mii_bus*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  in_interrupt () ; 
 int /*<<< orphan*/  mutex_lock_nested (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 

int mdiobus_read_nested(struct mii_bus *bus, int addr, u32 regnum)
{
	int retval;

	BUG_ON(in_interrupt());

	mutex_lock_nested(&bus->mdio_lock, MDIO_MUTEX_NESTED);
	retval = __mdiobus_read(bus, addr, regnum);
	mutex_unlock(&bus->mdio_lock);

	return retval;
}