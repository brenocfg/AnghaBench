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
typedef  int /*<<< orphan*/  xfrm_address_t ;
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct xfrm_state {int dummy; } ;
struct xfrm_mark {int dummy; } ;
struct TYPE_2__ {int /*<<< orphan*/  xfrm_state_lock; } ;
struct net {TYPE_1__ xfrm; } ;

/* Variables and functions */
 struct xfrm_state* __find_acq_core (struct net*,struct xfrm_mark const*,unsigned short,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/  const*,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

struct xfrm_state *
xfrm_find_acq(struct net *net, const struct xfrm_mark *mark, u8 mode, u32 reqid,
	      u32 if_id, u8 proto, const xfrm_address_t *daddr,
	      const xfrm_address_t *saddr, int create, unsigned short family)
{
	struct xfrm_state *x;

	spin_lock_bh(&net->xfrm.xfrm_state_lock);
	x = __find_acq_core(net, mark, family, mode, reqid, if_id, proto, daddr, saddr, create);
	spin_unlock_bh(&net->xfrm.xfrm_state_lock);

	return x;
}