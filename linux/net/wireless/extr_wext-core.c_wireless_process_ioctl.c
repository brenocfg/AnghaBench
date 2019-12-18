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
typedef  int (* wext_ioctl_func ) (struct net_device*,struct iwreq*,unsigned int,struct iw_request_info*,int /*<<< orphan*/ *) ;
struct net_device {scalar_t__ wireless_handlers; } ;
struct net {int dummy; } ;
struct iwreq {int /*<<< orphan*/  ifr_name; } ;
struct iw_request_info {int dummy; } ;
typedef  int /*<<< orphan*/ * iw_handler ;

/* Variables and functions */
 int ENODEV ; 
 int EOPNOTSUPP ; 
 unsigned int SIOCGIWPRIV ; 
 unsigned int SIOCGIWSTATS ; 
 unsigned int SIOCIWFIRSTPRIV ; 
 struct net_device* __dev_get_by_name (struct net*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/ * get_handler (struct net_device*,unsigned int) ; 
 int /*<<< orphan*/  iw_handler_get_iwstats ; 
 int /*<<< orphan*/ * iw_handler_get_private ; 
 int /*<<< orphan*/  netif_device_present (struct net_device*) ; 

__attribute__((used)) static int wireless_process_ioctl(struct net *net, struct iwreq *iwr,
				  unsigned int cmd,
				  struct iw_request_info *info,
				  wext_ioctl_func standard,
				  wext_ioctl_func private)
{
	struct net_device *dev;
	iw_handler	handler;

	/* Permissions are already checked in dev_ioctl() before calling us.
	 * The copy_to/from_user() of ifr is also dealt with in there */

	/* Make sure the device exist */
	if ((dev = __dev_get_by_name(net, iwr->ifr_name)) == NULL)
		return -ENODEV;

	/* A bunch of special cases, then the generic case...
	 * Note that 'cmd' is already filtered in dev_ioctl() with
	 * (cmd >= SIOCIWFIRST && cmd <= SIOCIWLAST) */
	if (cmd == SIOCGIWSTATS)
		return standard(dev, iwr, cmd, info,
				&iw_handler_get_iwstats);

#ifdef CONFIG_WEXT_PRIV
	if (cmd == SIOCGIWPRIV && dev->wireless_handlers)
		return standard(dev, iwr, cmd, info,
				iw_handler_get_private);
#endif

	/* Basic check */
	if (!netif_device_present(dev))
		return -ENODEV;

	/* New driver API : try to find the handler */
	handler = get_handler(dev, cmd);
	if (handler) {
		/* Standard and private are not the same */
		if (cmd < SIOCIWFIRSTPRIV)
			return standard(dev, iwr, cmd, info, handler);
		else if (private)
			return private(dev, iwr, cmd, info, handler);
	}
	return -EOPNOTSUPP;
}