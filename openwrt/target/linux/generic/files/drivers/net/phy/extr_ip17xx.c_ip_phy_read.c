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
struct ip17xx_state {int /*<<< orphan*/  mii_bus; } ;

/* Variables and functions */
 int mdiobus_read (int /*<<< orphan*/ ,int,int) ; 
 int /*<<< orphan*/  pr_debug (char*,int,int,int) ; 
 int /*<<< orphan*/  pr_warning (char*,int,int,int) ; 

__attribute__((used)) static int ip_phy_read(struct ip17xx_state *state, int port, int reg)
{
	int val = mdiobus_read(state->mii_bus, port, reg);
	if (val < 0)
		pr_warning("IP17xx: Unable to get MII register %d,%d: error %d\n", port, reg, -val);
#ifdef DUMP_MII_IO
	else
		pr_debug("IP17xx: Read MII(%d,%d) -> %04x\n", port, reg, val);
#endif
	return val;
}