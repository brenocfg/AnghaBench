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
struct net_device {int dummy; } ;
struct ave_private {scalar_t__ base; } ;

/* Variables and functions */
 scalar_t__ AVE_PFMBIT (unsigned int) ; 
 int AVE_PFMBIT_MASK ; 
 scalar_t__ AVE_PFMBYTE (unsigned int) ; 
 int AVE_PFMBYTE_MASK0 ; 
 int AVE_PFMBYTE_MASK1 ; 
 scalar_t__ AVE_PFSEL (unsigned int) ; 
 unsigned int AVE_PF_SIZE ; 
 scalar_t__ AVE_PKTF (unsigned int) ; 
 int EINVAL ; 
 int GENMASK (int,unsigned int) ; 
 scalar_t__ WARN_ON (int) ; 
 int /*<<< orphan*/  ave_hw_write_macaddr (struct net_device*,unsigned char const*,scalar_t__,scalar_t__) ; 
 int /*<<< orphan*/  ave_pfsel_start (struct net_device*,unsigned int) ; 
 int /*<<< orphan*/  ave_pfsel_stop (struct net_device*,unsigned int) ; 
 struct ave_private* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  writel (int,scalar_t__) ; 

__attribute__((used)) static int ave_pfsel_set_macaddr(struct net_device *ndev,
				 unsigned int entry,
				 const unsigned char *mac_addr,
				 unsigned int set_size)
{
	struct ave_private *priv = netdev_priv(ndev);

	if (WARN_ON(entry > AVE_PF_SIZE))
		return -EINVAL;
	if (WARN_ON(set_size > 6))
		return -EINVAL;

	ave_pfsel_stop(ndev, entry);

	/* set MAC address for the filter */
	ave_hw_write_macaddr(ndev, mac_addr,
			     AVE_PKTF(entry), AVE_PKTF(entry) + 4);

	/* set byte mask */
	writel(GENMASK(31, set_size) & AVE_PFMBYTE_MASK0,
	       priv->base + AVE_PFMBYTE(entry));
	writel(AVE_PFMBYTE_MASK1, priv->base + AVE_PFMBYTE(entry) + 4);

	/* set bit mask filter */
	writel(AVE_PFMBIT_MASK, priv->base + AVE_PFMBIT(entry));

	/* set selector to ring 0 */
	writel(0, priv->base + AVE_PFSEL(entry));

	/* restart filter */
	ave_pfsel_start(ndev, entry);

	return 0;
}