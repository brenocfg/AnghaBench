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
struct temac_local {int (* dma_in ) (struct temac_local*,int) ;} ;
struct net_device {int dummy; } ;
struct device_attribute {int dummy; } ;
struct device {int dummy; } ;
typedef  int ssize_t ;

/* Variables and functions */
 struct net_device* dev_get_drvdata (struct device*) ; 
 struct temac_local* netdev_priv (struct net_device*) ; 
 scalar_t__ sprintf (char*,char*,...) ; 
 int stub1 (struct temac_local*,int) ; 
 int stub2 (struct temac_local*,int) ; 

__attribute__((used)) static ssize_t temac_show_llink_regs(struct device *dev,
				     struct device_attribute *attr, char *buf)
{
	struct net_device *ndev = dev_get_drvdata(dev);
	struct temac_local *lp = netdev_priv(ndev);
	int i, len = 0;

	for (i = 0; i < 0x11; i++)
		len += sprintf(buf + len, "%.8x%s", lp->dma_in(lp, i),
			       (i % 8) == 7 ? "\n" : " ");
	len += sprintf(buf + len, "\n");

	return len;
}