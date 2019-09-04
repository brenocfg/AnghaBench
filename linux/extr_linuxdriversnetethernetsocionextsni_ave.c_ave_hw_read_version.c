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
struct net_device {int dummy; } ;
struct ave_private {scalar_t__ base; } ;

/* Variables and functions */
 scalar_t__ AVE_VR ; 
 int GENMASK (int,int) ; 
 struct ave_private* netdev_priv (struct net_device*) ; 
 int readl (scalar_t__) ; 
 int /*<<< orphan*/  snprintf (char*,int,char*,int,int) ; 

__attribute__((used)) static void ave_hw_read_version(struct net_device *ndev, char *buf, int len)
{
	struct ave_private *priv = netdev_priv(ndev);
	u32 major, minor, vr;

	vr = readl(priv->base + AVE_VR);
	major = (vr & GENMASK(15, 8)) >> 8;
	minor = (vr & GENMASK(7, 0));
	snprintf(buf, len, "v%u.%u", major, minor);
}