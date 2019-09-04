#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_8__   TYPE_4__ ;
typedef  struct TYPE_7__   TYPE_3__ ;
typedef  struct TYPE_6__   TYPE_2__ ;
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ u64 ;
struct inet6_ifaddr {int flags; int /*<<< orphan*/  dad_probes; scalar_t__ dad_nonce; struct inet6_dev* idev; } ;
struct TYPE_7__ {int /*<<< orphan*/  dad_transmits; scalar_t__ enhanced_dad; scalar_t__ rtr_solicit_delay; } ;
struct inet6_dev {TYPE_3__ cnf; int /*<<< orphan*/  dev; } ;
struct TYPE_6__ {TYPE_1__* devconf_all; } ;
struct TYPE_8__ {TYPE_2__ ipv6; } ;
struct TYPE_5__ {scalar_t__ enhanced_dad; } ;

/* Variables and functions */
 int IFA_F_OPTIMISTIC ; 
 int /*<<< orphan*/  addrconf_mod_dad_work (struct inet6_ifaddr*,unsigned long) ; 
 TYPE_4__* dev_net (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  get_random_bytes (scalar_t__*,int) ; 
 int prandom_u32 () ; 

__attribute__((used)) static void addrconf_dad_kick(struct inet6_ifaddr *ifp)
{
	unsigned long rand_num;
	struct inet6_dev *idev = ifp->idev;
	u64 nonce;

	if (ifp->flags & IFA_F_OPTIMISTIC)
		rand_num = 0;
	else
		rand_num = prandom_u32() % (idev->cnf.rtr_solicit_delay ? : 1);

	nonce = 0;
	if (idev->cnf.enhanced_dad ||
	    dev_net(idev->dev)->ipv6.devconf_all->enhanced_dad) {
		do
			get_random_bytes(&nonce, 6);
		while (nonce == 0);
	}
	ifp->dad_nonce = nonce;
	ifp->dad_probes = idev->cnf.dad_transmits;
	addrconf_mod_dad_work(ifp, rand_num);
}