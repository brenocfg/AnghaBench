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
struct zd1201 {int /*<<< orphan*/  ap; } ;
struct net_device {int dummy; } ;
struct iw_request_info {int dummy; } ;
struct iw_param {int /*<<< orphan*/  value; } ;

/* Variables and functions */
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  ZD1201_RID_CNFHOSTAUTH ; 
 struct zd1201* netdev_priv (struct net_device*) ; 
 int zd1201_setconfig16 (struct zd1201*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int zd1201_set_hostauth(struct net_device *dev,
    struct iw_request_info *info, struct iw_param *rrq, char *extra)
{
	struct zd1201 *zd = netdev_priv(dev);

	if (!zd->ap)
		return -EOPNOTSUPP;

	return zd1201_setconfig16(zd, ZD1201_RID_CNFHOSTAUTH, rrq->value);
}