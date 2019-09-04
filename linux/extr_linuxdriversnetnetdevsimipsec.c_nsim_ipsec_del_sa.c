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
typedef  size_t u16 ;
struct TYPE_3__ {size_t offload_handle; int /*<<< orphan*/  dev; } ;
struct xfrm_state {TYPE_1__ xso; } ;
struct nsim_sa {int dummy; } ;
struct nsim_ipsec {int /*<<< orphan*/  count; TYPE_2__* sa; } ;
struct netdevsim {int /*<<< orphan*/  netdev; struct nsim_ipsec ipsec; } ;
struct TYPE_4__ {int /*<<< orphan*/  used; } ;

/* Variables and functions */
 size_t NSIM_IPSEC_VALID ; 
 int /*<<< orphan*/  memset (TYPE_2__*,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  netdev_err (int /*<<< orphan*/ ,char*,size_t) ; 
 struct netdevsim* netdev_priv (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void nsim_ipsec_del_sa(struct xfrm_state *xs)
{
	struct netdevsim *ns = netdev_priv(xs->xso.dev);
	struct nsim_ipsec *ipsec = &ns->ipsec;
	u16 sa_idx;

	sa_idx = xs->xso.offload_handle & ~NSIM_IPSEC_VALID;
	if (!ipsec->sa[sa_idx].used) {
		netdev_err(ns->netdev, "Invalid SA for delete sa_idx=%d\n",
			   sa_idx);
		return;
	}

	memset(&ipsec->sa[sa_idx], 0, sizeof(struct nsim_sa));
	ipsec->count--;
}