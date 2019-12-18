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
struct mii_bus {int dummy; } ;

/* Variables and functions */
 int AR8XXX_NUM_PHYS ; 
 int BMCR_RESET ; 
 int ETIMEDOUT ; 
 int /*<<< orphan*/  MII_BMCR ; 
 int mdiobus_read (struct mii_bus*,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  msleep (unsigned int) ; 
 int /*<<< orphan*/  usleep_range (int,int) ; 

__attribute__((used)) static int
ar8xxx_phy_poll_reset(struct mii_bus *bus)
{
        unsigned int sleep_msecs = 20;
        int ret, elapsed, i;

        for (elapsed = sleep_msecs; elapsed <= 600;
	     elapsed += sleep_msecs) {
                msleep(sleep_msecs);
                for (i = 0; i < AR8XXX_NUM_PHYS; i++) {
                        ret = mdiobus_read(bus, i, MII_BMCR);
                        if (ret < 0)
				return ret;
                        if (ret & BMCR_RESET)
				break;
                        if (i == AR8XXX_NUM_PHYS - 1) {
                                usleep_range(1000, 2000);
                                return 0;
                        }
                }
        }
        return -ETIMEDOUT;
}