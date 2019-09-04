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
struct TYPE_4__ {int /*<<< orphan*/  s_addr; } ;
struct sockaddr_in {TYPE_2__ sin_addr; int /*<<< orphan*/  sin_family; } ;
struct sockaddr {int dummy; } ;
struct notifier_block {int dummy; } ;
struct nfsd_net {int /*<<< orphan*/  ntf_wq; int /*<<< orphan*/  ntf_refcnt; scalar_t__ nfsd_serv; } ;
struct net_device {int dummy; } ;
struct net {int dummy; } ;
struct in_ifaddr {int /*<<< orphan*/  ifa_local; TYPE_1__* ifa_dev; } ;
struct TYPE_3__ {struct net_device* dev; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 unsigned long NETDEV_DOWN ; 
 int NOTIFY_DONE ; 
 int /*<<< orphan*/  atomic_dec (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  atomic_inc_not_zero (int /*<<< orphan*/ *) ; 
 struct net* dev_net (struct net_device*) ; 
 int /*<<< orphan*/  dprintk (char*,int /*<<< orphan*/ *) ; 
 struct nfsd_net* net_generic (struct net*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nfsd_net_id ; 
 int /*<<< orphan*/  svc_age_temp_xprts_now (scalar_t__,struct sockaddr*) ; 
 int /*<<< orphan*/  wake_up (int /*<<< orphan*/ *) ; 

__attribute__((used)) static int nfsd_inetaddr_event(struct notifier_block *this, unsigned long event,
	void *ptr)
{
	struct in_ifaddr *ifa = (struct in_ifaddr *)ptr;
	struct net_device *dev = ifa->ifa_dev->dev;
	struct net *net = dev_net(dev);
	struct nfsd_net *nn = net_generic(net, nfsd_net_id);
	struct sockaddr_in sin;

	if ((event != NETDEV_DOWN) ||
	    !atomic_inc_not_zero(&nn->ntf_refcnt))
		goto out;

	if (nn->nfsd_serv) {
		dprintk("nfsd_inetaddr_event: removed %pI4\n", &ifa->ifa_local);
		sin.sin_family = AF_INET;
		sin.sin_addr.s_addr = ifa->ifa_local;
		svc_age_temp_xprts_now(nn->nfsd_serv, (struct sockaddr *)&sin);
	}
	atomic_dec(&nn->ntf_refcnt);
	wake_up(&nn->ntf_wq);

out:
	return NOTIFY_DONE;
}