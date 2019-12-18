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
typedef  int /*<<< orphan*/  wext_ioctl_func ;
struct net {int dummy; } ;
struct iwreq {int /*<<< orphan*/  ifr_name; } ;
struct iw_request_info {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  dev_load (struct net*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtnl_lock () ; 
 int /*<<< orphan*/  rtnl_unlock () ; 
 int wext_permission_check (unsigned int) ; 
 int wireless_process_ioctl (struct net*,struct iwreq*,unsigned int,struct iw_request_info*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static int wext_ioctl_dispatch(struct net *net, struct iwreq *iwr,
			       unsigned int cmd, struct iw_request_info *info,
			       wext_ioctl_func standard,
			       wext_ioctl_func private)
{
	int ret = wext_permission_check(cmd);

	if (ret)
		return ret;

	dev_load(net, iwr->ifr_name);
	rtnl_lock();
	ret = wireless_process_ioctl(net, iwr, cmd, info, standard, private);
	rtnl_unlock();

	return ret;
}