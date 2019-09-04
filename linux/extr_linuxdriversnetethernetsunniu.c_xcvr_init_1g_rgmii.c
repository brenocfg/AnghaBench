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
typedef  int /*<<< orphan*/  u64 ;
typedef  int u16 ;
struct niu {int /*<<< orphan*/  phy_addr; } ;

/* Variables and functions */
 int ADVERTISE_1000FULL ; 
 int BMCR_FULLDPLX ; 
 int BMCR_SPEED1000 ; 
 int BMSR_ESTATEN ; 
 int ESTATUS_1000_TFULL ; 
 int /*<<< orphan*/  MIF_CONFIG ; 
 int /*<<< orphan*/  MIF_CONFIG_INDIRECT_MODE ; 
 int /*<<< orphan*/  MII_BMCR ; 
 int /*<<< orphan*/  MII_BMSR ; 
 int /*<<< orphan*/  MII_CTRL1000 ; 
 int /*<<< orphan*/  MII_ESTATUS ; 
 int mii_read (struct niu*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int mii_reset (struct niu*) ; 
 int mii_write (struct niu*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  nr64 (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nw64 (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int xcvr_init_1g_rgmii(struct niu *np)
{
	int err;
	u64 val;
	u16 bmcr, bmsr, estat;

	val = nr64(MIF_CONFIG);
	val &= ~MIF_CONFIG_INDIRECT_MODE;
	nw64(MIF_CONFIG, val);

	err = mii_reset(np);
	if (err)
		return err;

	err = mii_read(np, np->phy_addr, MII_BMSR);
	if (err < 0)
		return err;
	bmsr = err;

	estat = 0;
	if (bmsr & BMSR_ESTATEN) {
		err = mii_read(np, np->phy_addr, MII_ESTATUS);
		if (err < 0)
			return err;
		estat = err;
	}

	bmcr = 0;
	err = mii_write(np, np->phy_addr, MII_BMCR, bmcr);
	if (err)
		return err;

	if (bmsr & BMSR_ESTATEN) {
		u16 ctrl1000 = 0;

		if (estat & ESTATUS_1000_TFULL)
			ctrl1000 |= ADVERTISE_1000FULL;
		err = mii_write(np, np->phy_addr, MII_CTRL1000, ctrl1000);
		if (err)
			return err;
	}

	bmcr = (BMCR_SPEED1000 | BMCR_FULLDPLX);

	err = mii_write(np, np->phy_addr, MII_BMCR, bmcr);
	if (err)
		return err;

	err = mii_read(np, np->phy_addr, MII_BMCR);
	if (err < 0)
		return err;
	bmcr = mii_read(np, np->phy_addr, MII_BMCR);

	err = mii_read(np, np->phy_addr, MII_BMSR);
	if (err < 0)
		return err;

	return 0;
}