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
typedef  int /*<<< orphan*/  u16 ;
struct TYPE_2__ {int /*<<< orphan*/  bus; } ;
struct phy_device {TYPE_1__ mdio; } ;

/* Variables and functions */
 int /*<<< orphan*/  BROADCAST_ADDR ; 
 int mdiobus_write (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int broadcast_write(struct phy_device *phydev, u32 regnum,
				  u16 val)
{
	return mdiobus_write(phydev->mdio.bus, BROADCAST_ADDR, regnum, val);
}