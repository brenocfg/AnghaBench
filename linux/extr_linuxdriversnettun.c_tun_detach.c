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
struct tun_struct {struct net_device* dev; } ;
struct tun_file {int /*<<< orphan*/  tun; } ;
struct net_device {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  __tun_detach (struct tun_file*,int) ; 
 int /*<<< orphan*/  netdev_state_change (struct net_device*) ; 
 struct tun_struct* rtnl_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rtnl_lock () ; 
 int /*<<< orphan*/  rtnl_unlock () ; 

__attribute__((used)) static void tun_detach(struct tun_file *tfile, bool clean)
{
	struct tun_struct *tun;
	struct net_device *dev;

	rtnl_lock();
	tun = rtnl_dereference(tfile->tun);
	dev = tun ? tun->dev : NULL;
	__tun_detach(tfile, clean);
	if (dev)
		netdev_state_change(dev);
	rtnl_unlock();
}