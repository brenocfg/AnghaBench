#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct xfrmk_sadinfo {int /*<<< orphan*/  sadhmcnt; scalar_t__ sadhcnt; int /*<<< orphan*/  sadcnt; } ;
struct TYPE_2__ {int /*<<< orphan*/  xfrm_state_lock; scalar_t__ state_hmask; int /*<<< orphan*/  state_num; } ;
struct net {TYPE_1__ xfrm; } ;

/* Variables and functions */
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  xfrm_state_hashmax ; 

void xfrm_sad_getinfo(struct net *net, struct xfrmk_sadinfo *si)
{
	spin_lock_bh(&net->xfrm.xfrm_state_lock);
	si->sadcnt = net->xfrm.state_num;
	si->sadhcnt = net->xfrm.state_hmask + 1;
	si->sadhmcnt = xfrm_state_hashmax;
	spin_unlock_bh(&net->xfrm.xfrm_state_lock);
}