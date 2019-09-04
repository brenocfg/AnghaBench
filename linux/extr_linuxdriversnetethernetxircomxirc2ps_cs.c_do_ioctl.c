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
struct net_device {unsigned int base_addr; int /*<<< orphan*/  name; } ;
struct mii_ioctl_data {int phy_id; int reg_num; int /*<<< orphan*/  val_in; int /*<<< orphan*/  val_out; } ;
struct local_info {int /*<<< orphan*/  mohawk; } ;
struct TYPE_2__ {int /*<<< orphan*/  ifrn_name; } ;
struct ifreq {TYPE_1__ ifr_ifrn; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
#define  SIOCGMIIPHY 130 
#define  SIOCGMIIREG 129 
#define  SIOCSMIIREG 128 
 struct mii_ioctl_data* if_mii (struct ifreq*) ; 
 int /*<<< orphan*/  mii_rd (unsigned int,int,int) ; 
 int /*<<< orphan*/  mii_wr (unsigned int,int,int,int /*<<< orphan*/ ,int) ; 
 struct local_info* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  pr_debug (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,int,int,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
do_ioctl(struct net_device *dev, struct ifreq *rq, int cmd)
{
    struct local_info *local = netdev_priv(dev);
    unsigned int ioaddr = dev->base_addr;
    struct mii_ioctl_data *data = if_mii(rq);

    pr_debug("%s: ioctl(%-.6s, %#04x) %04x %04x %04x %04x\n",
	  dev->name, rq->ifr_ifrn.ifrn_name, cmd,
	  data->phy_id, data->reg_num, data->val_in, data->val_out);

    if (!local->mohawk)
	return -EOPNOTSUPP;

    switch(cmd) {
      case SIOCGMIIPHY:		/* Get the address of the PHY in use. */
	data->phy_id = 0;	/* we have only this address */
	/* fall through */
      case SIOCGMIIREG:		/* Read the specified MII register. */
	data->val_out = mii_rd(ioaddr, data->phy_id & 0x1f,
			       data->reg_num & 0x1f);
	break;
      case SIOCSMIIREG:		/* Write the specified MII register */
	mii_wr(ioaddr, data->phy_id & 0x1f, data->reg_num & 0x1f, data->val_in,
	       16);
	break;
      default:
	return -EOPNOTSUPP;
    }
    return 0;
}