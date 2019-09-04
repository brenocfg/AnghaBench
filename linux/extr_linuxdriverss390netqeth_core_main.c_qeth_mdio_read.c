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
struct TYPE_4__ {int rx_errors; } ;
struct TYPE_3__ {int /*<<< orphan*/  link_type; } ;
struct qeth_card {TYPE_2__ stats; TYPE_1__ info; } ;
struct net_device {int* dev_addr; struct qeth_card* ml_priv; } ;

/* Variables and functions */
 int ADVERTISE_ALL ; 
 int BMCR_FULLDPLX ; 
 int BMCR_SPEED100 ; 
 int BMSR_100BASE4 ; 
 int BMSR_100FULL ; 
 int BMSR_100HALF ; 
 int BMSR_10FULL ; 
 int BMSR_10HALF ; 
 int BMSR_ANEGCOMPLETE ; 
 int BMSR_ERCAP ; 
 int BMSR_LSTATUS ; 
 int LPA_100BASE4 ; 
 int LPA_100FULL ; 
 int LPA_100HALF ; 
 int LPA_10FULL ; 
 int LPA_10HALF ; 
 int LPA_LPACK ; 
#define  MII_ADVERTISE 145 
#define  MII_BMCR 144 
#define  MII_BMSR 143 
#define  MII_DCOUNTER 142 
#define  MII_EXPANSION 141 
#define  MII_FCSCOUNTER 140 
#define  MII_LBRERROR 139 
#define  MII_LPA 138 
#define  MII_NCONFIG 137 
#define  MII_NWAYTEST 136 
#define  MII_PHYADDR 135 
#define  MII_PHYSID1 134 
#define  MII_PHYSID2 133 
#define  MII_RERRCOUNTER 132 
#define  MII_RESV1 131 
#define  MII_RESV2 130 
#define  MII_SREVISION 129 
#define  MII_TPISTATUS 128 
 int /*<<< orphan*/  QETH_LINK_TYPE_10GBIT_ETH ; 
 int /*<<< orphan*/  QETH_LINK_TYPE_GBIT_ETH ; 
 int /*<<< orphan*/  QETH_LINK_TYPE_OSN ; 

__attribute__((used)) static int qeth_mdio_read(struct net_device *dev, int phy_id, int regnum)
{
	struct qeth_card *card = dev->ml_priv;
	int rc = 0;

	switch (regnum) {
	case MII_BMCR: /* Basic mode control register */
		rc = BMCR_FULLDPLX;
		if ((card->info.link_type != QETH_LINK_TYPE_GBIT_ETH) &&
		    (card->info.link_type != QETH_LINK_TYPE_OSN) &&
		    (card->info.link_type != QETH_LINK_TYPE_10GBIT_ETH))
			rc |= BMCR_SPEED100;
		break;
	case MII_BMSR: /* Basic mode status register */
		rc = BMSR_ERCAP | BMSR_ANEGCOMPLETE | BMSR_LSTATUS |
		     BMSR_10HALF | BMSR_10FULL | BMSR_100HALF | BMSR_100FULL |
		     BMSR_100BASE4;
		break;
	case MII_PHYSID1: /* PHYS ID 1 */
		rc = (dev->dev_addr[0] << 16) | (dev->dev_addr[1] << 8) |
		     dev->dev_addr[2];
		rc = (rc >> 5) & 0xFFFF;
		break;
	case MII_PHYSID2: /* PHYS ID 2 */
		rc = (dev->dev_addr[2] << 10) & 0xFFFF;
		break;
	case MII_ADVERTISE: /* Advertisement control reg */
		rc = ADVERTISE_ALL;
		break;
	case MII_LPA: /* Link partner ability reg */
		rc = LPA_10HALF | LPA_10FULL | LPA_100HALF | LPA_100FULL |
		     LPA_100BASE4 | LPA_LPACK;
		break;
	case MII_EXPANSION: /* Expansion register */
		break;
	case MII_DCOUNTER: /* disconnect counter */
		break;
	case MII_FCSCOUNTER: /* false carrier counter */
		break;
	case MII_NWAYTEST: /* N-way auto-neg test register */
		break;
	case MII_RERRCOUNTER: /* rx error counter */
		rc = card->stats.rx_errors;
		break;
	case MII_SREVISION: /* silicon revision */
		break;
	case MII_RESV1: /* reserved 1 */
		break;
	case MII_LBRERROR: /* loopback, rx, bypass error */
		break;
	case MII_PHYADDR: /* physical address */
		break;
	case MII_RESV2: /* reserved 2 */
		break;
	case MII_TPISTATUS: /* TPI status for 10mbps */
		break;
	case MII_NCONFIG: /* network interface config */
		break;
	default:
		break;
	}
	return rc;
}