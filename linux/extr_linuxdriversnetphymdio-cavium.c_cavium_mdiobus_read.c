#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_2__ ;
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {int dat; scalar_t__ val; scalar_t__ pending; } ;
union cvmx_smix_rd_dat {TYPE_2__ s; int /*<<< orphan*/  u64; } ;
struct TYPE_3__ {unsigned int phy_op; int phy_adr; int reg_adr; } ;
union cvmx_smix_cmd {scalar_t__ u64; TYPE_1__ s; } ;
struct mii_bus {struct cavium_mdiobus* priv; } ;
struct cavium_mdiobus {scalar_t__ register_base; } ;

/* Variables and functions */
 int /*<<< orphan*/  C22 ; 
 int EIO ; 
 int MII_ADDR_C45 ; 
 scalar_t__ SMI_CMD ; 
 scalar_t__ SMI_RD_DAT ; 
 int /*<<< orphan*/  __delay (int) ; 
 int cavium_mdiobus_c45_addr (struct cavium_mdiobus*,int,int) ; 
 int /*<<< orphan*/  cavium_mdiobus_set_mode (struct cavium_mdiobus*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  oct_mdio_readq (scalar_t__) ; 
 int /*<<< orphan*/  oct_mdio_writeq (scalar_t__,scalar_t__) ; 

int cavium_mdiobus_read(struct mii_bus *bus, int phy_id, int regnum)
{
	struct cavium_mdiobus *p = bus->priv;
	union cvmx_smix_cmd smi_cmd;
	union cvmx_smix_rd_dat smi_rd;
	unsigned int op = 1; /* MDIO_CLAUSE_22_READ */
	int timeout = 1000;

	if (regnum & MII_ADDR_C45) {
		int r = cavium_mdiobus_c45_addr(p, phy_id, regnum);

		if (r < 0)
			return r;

		regnum = (regnum >> 16) & 0x1f;
		op = 3; /* MDIO_CLAUSE_45_READ */
	} else {
		cavium_mdiobus_set_mode(p, C22);
	}

	smi_cmd.u64 = 0;
	smi_cmd.s.phy_op = op;
	smi_cmd.s.phy_adr = phy_id;
	smi_cmd.s.reg_adr = regnum;
	oct_mdio_writeq(smi_cmd.u64, p->register_base + SMI_CMD);

	do {
		/* Wait 1000 clocks so we don't saturate the RSL bus
		 * doing reads.
		 */
		__delay(1000);
		smi_rd.u64 = oct_mdio_readq(p->register_base + SMI_RD_DAT);
	} while (smi_rd.s.pending && --timeout);

	if (smi_rd.s.val)
		return smi_rd.s.dat;
	else
		return -EIO;
}