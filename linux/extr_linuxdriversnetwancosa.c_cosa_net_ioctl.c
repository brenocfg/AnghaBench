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
struct ifreq {scalar_t__ ifr_data; } ;
struct channel_data {int /*<<< orphan*/  cosa; } ;

/* Variables and functions */
 int ENOIOCTLCMD ; 
 int cosa_ioctl_common (int /*<<< orphan*/ ,struct channel_data*,int,unsigned long) ; 
 struct channel_data* dev_to_chan (struct net_device*) ; 
 int hdlc_ioctl (struct net_device*,struct ifreq*,int) ; 

__attribute__((used)) static int cosa_net_ioctl(struct net_device *dev, struct ifreq *ifr, int cmd)
{
	int rv;
	struct channel_data *chan = dev_to_chan(dev);
	rv = cosa_ioctl_common(chan->cosa, chan, cmd,
			       (unsigned long)ifr->ifr_data);
	if (rv != -ENOIOCTLCMD)
		return rv;
	return hdlc_ioctl(dev, ifr, cmd);
}