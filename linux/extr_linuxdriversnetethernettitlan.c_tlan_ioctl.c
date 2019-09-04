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
typedef  int u32 ;
struct tlan_priv {int* phy; size_t phy_num; int /*<<< orphan*/  phy_online; } ;
struct net_device {int dummy; } ;
struct mii_ioctl_data {int phy_id; int reg_num; int /*<<< orphan*/  val_in; int /*<<< orphan*/  val_out; } ;
struct ifreq {int dummy; } ;

/* Variables and functions */
 int EAGAIN ; 
 int EOPNOTSUPP ; 
#define  SIOCGMIIPHY 130 
#define  SIOCGMIIREG 129 
#define  SIOCSMIIREG 128 
 struct mii_ioctl_data* if_mii (struct ifreq*) ; 
 struct tlan_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  tlan_mii_read_reg (struct net_device*,int,int,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  tlan_mii_write_reg (struct net_device*,int,int,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int tlan_ioctl(struct net_device *dev, struct ifreq *rq, int cmd)
{
	struct tlan_priv *priv = netdev_priv(dev);
	struct mii_ioctl_data *data = if_mii(rq);
	u32 phy   = priv->phy[priv->phy_num];

	if (!priv->phy_online)
		return -EAGAIN;

	switch (cmd) {
	case SIOCGMIIPHY:		/* get address of MII PHY in use. */
		data->phy_id = phy;
		/* fall through */


	case SIOCGMIIREG:		/* read MII PHY register. */
		tlan_mii_read_reg(dev, data->phy_id & 0x1f,
				  data->reg_num & 0x1f, &data->val_out);
		return 0;


	case SIOCSMIIREG:		/* write MII PHY register. */
		tlan_mii_write_reg(dev, data->phy_id & 0x1f,
				   data->reg_num & 0x1f, data->val_in);
		return 0;
	default:
		return -EOPNOTSUPP;
	}
}