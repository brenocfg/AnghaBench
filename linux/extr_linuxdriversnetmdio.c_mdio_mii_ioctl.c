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
typedef  int u16 ;
struct mii_ioctl_data {int reg_num; int phy_id; int val_out; int /*<<< orphan*/  val_in; } ;
struct mdio_if_info {int prtad; int mode_support; int mmds; int (* mdio_read ) (int /*<<< orphan*/ ,int,int,int) ;int (* mdio_write ) (int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ ) ;int /*<<< orphan*/  dev; } ;

/* Variables and functions */
 int EINVAL ; 
 int EOPNOTSUPP ; 
 int MDIO_AN_ADVERTISE ; 
 int MDIO_AN_LPA ; 
 int MDIO_DEVAD_NONE ; 
 int MDIO_DEVS_AN ; 
 int MDIO_EMULATE_C22 ; 
 int MDIO_MMD_AN ; 
 int MDIO_PRTAD_NONE ; 
 int MDIO_SUPPORTS_C22 ; 
 int MDIO_SUPPORTS_C45 ; 
#define  MII_ADVERTISE 136 
#define  MII_BMCR 135 
#define  MII_BMSR 134 
#define  MII_LPA 133 
#define  MII_PHYSID1 132 
#define  MII_PHYSID2 131 
#define  SIOCGMIIPHY 130 
#define  SIOCGMIIREG 129 
#define  SIOCSMIIREG 128 
 int __ffs (int) ; 
 int mdio_phy_id_devad (int) ; 
 scalar_t__ mdio_phy_id_is_c45 (int) ; 
 int mdio_phy_id_prtad (int) ; 
 int stub1 (int /*<<< orphan*/ ,int,int,int) ; 
 int stub2 (int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ ) ; 

int mdio_mii_ioctl(const struct mdio_if_info *mdio,
		   struct mii_ioctl_data *mii_data, int cmd)
{
	int prtad, devad;
	u16 addr = mii_data->reg_num;

	/* Validate/convert cmd to one of SIOC{G,S}MIIREG */
	switch (cmd) {
	case SIOCGMIIPHY:
		if (mdio->prtad == MDIO_PRTAD_NONE)
			return -EOPNOTSUPP;
		mii_data->phy_id = mdio->prtad;
		cmd = SIOCGMIIREG;
		break;
	case SIOCGMIIREG:
	case SIOCSMIIREG:
		break;
	default:
		return -EOPNOTSUPP;
	}

	/* Validate/convert phy_id */
	if ((mdio->mode_support & MDIO_SUPPORTS_C45) &&
	    mdio_phy_id_is_c45(mii_data->phy_id)) {
		prtad = mdio_phy_id_prtad(mii_data->phy_id);
		devad = mdio_phy_id_devad(mii_data->phy_id);
	} else if ((mdio->mode_support & MDIO_SUPPORTS_C22) &&
		   mii_data->phy_id < 0x20) {
		prtad = mii_data->phy_id;
		devad = MDIO_DEVAD_NONE;
		addr &= 0x1f;
	} else if ((mdio->mode_support & MDIO_EMULATE_C22) &&
		   mdio->prtad != MDIO_PRTAD_NONE &&
		   mii_data->phy_id == mdio->prtad) {
		/* Remap commonly-used MII registers. */
		prtad = mdio->prtad;
		switch (addr) {
		case MII_BMCR:
		case MII_BMSR:
		case MII_PHYSID1:
		case MII_PHYSID2:
			devad = __ffs(mdio->mmds);
			break;
		case MII_ADVERTISE:
		case MII_LPA:
			if (!(mdio->mmds & MDIO_DEVS_AN))
				return -EINVAL;
			devad = MDIO_MMD_AN;
			if (addr == MII_ADVERTISE)
				addr = MDIO_AN_ADVERTISE;
			else
				addr = MDIO_AN_LPA;
			break;
		default:
			return -EINVAL;
		}
	} else {
		return -EINVAL;
	}

	if (cmd == SIOCGMIIREG) {
		int rc = mdio->mdio_read(mdio->dev, prtad, devad, addr);
		if (rc < 0)
			return rc;
		mii_data->val_out = rc;
		return 0;
	} else {
		return mdio->mdio_write(mdio->dev, prtad, devad, addr,
					mii_data->val_in);
	}
}