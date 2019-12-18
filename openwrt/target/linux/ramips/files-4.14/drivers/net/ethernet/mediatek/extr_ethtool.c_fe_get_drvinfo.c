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
struct net_device {int dummy; } ;
struct fe_soc_data {scalar_t__* reg_table; } ;
struct fe_priv {TYPE_2__* dev; struct fe_soc_data* soc; } ;
struct ethtool_drvinfo {int /*<<< orphan*/  n_stats; int /*<<< orphan*/  bus_info; int /*<<< orphan*/  version; int /*<<< orphan*/  driver; } ;
struct TYPE_4__ {TYPE_1__* driver; } ;
struct TYPE_3__ {int /*<<< orphan*/  name; } ;

/* Variables and functions */
 int /*<<< orphan*/  ARRAY_SIZE (int /*<<< orphan*/ ) ; 
 size_t FE_REG_FE_COUNTER_BASE ; 
 int /*<<< orphan*/  MTK_FE_DRV_VERSION ; 
 int /*<<< orphan*/  dev_name (TYPE_2__*) ; 
 int /*<<< orphan*/  fe_gdma_str ; 
 struct fe_priv* netdev_priv (struct net_device*) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void fe_get_drvinfo(struct net_device *dev,
			   struct ethtool_drvinfo *info)
{
	struct fe_priv *priv = netdev_priv(dev);
	struct fe_soc_data *soc = priv->soc;

	strlcpy(info->driver, priv->dev->driver->name, sizeof(info->driver));
	strlcpy(info->version, MTK_FE_DRV_VERSION, sizeof(info->version));
	strlcpy(info->bus_info, dev_name(priv->dev), sizeof(info->bus_info));

	if (soc->reg_table[FE_REG_FE_COUNTER_BASE])
		info->n_stats = ARRAY_SIZE(fe_gdma_str);
}