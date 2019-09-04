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
struct net_device {struct lbs_private* ml_priv; } ;
struct lbs_private {int fwrelease; } ;
struct ethtool_drvinfo {int /*<<< orphan*/  version; int /*<<< orphan*/  driver; int /*<<< orphan*/  fw_version; } ;

/* Variables and functions */
 char* lbs_driver_version ; 
 int /*<<< orphan*/  snprintf (int /*<<< orphan*/ ,int,char*,int,int,int,int) ; 
 int /*<<< orphan*/  strlcpy (int /*<<< orphan*/ ,char*,int) ; 

__attribute__((used)) static void lbs_ethtool_get_drvinfo(struct net_device *dev,
					 struct ethtool_drvinfo *info)
{
	struct lbs_private *priv = dev->ml_priv;

	snprintf(info->fw_version, sizeof(info->fw_version),
		"%u.%u.%u.p%u",
		priv->fwrelease >> 24 & 0xff,
		priv->fwrelease >> 16 & 0xff,
		priv->fwrelease >>  8 & 0xff,
		priv->fwrelease       & 0xff);
	strlcpy(info->driver, "libertas", sizeof(info->driver));
	strlcpy(info->version, lbs_driver_version, sizeof(info->version));
}