#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_3__ ;
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct xfrm_state_afinfo {int (* extract_output ) (struct xfrm_state*,struct sk_buff*) ;} ;
struct xfrm_mode {int /*<<< orphan*/  family; } ;
struct TYPE_4__ {scalar_t__ family; } ;
struct xfrm_state {struct xfrm_mode inner_mode; TYPE_1__ sel; } ;
struct sk_buff {int dummy; } ;
struct TYPE_6__ {TYPE_2__* ops; } ;
struct TYPE_5__ {int /*<<< orphan*/  family; } ;

/* Variables and functions */
 scalar_t__ AF_UNSPEC ; 
 int EAFNOSUPPORT ; 
 scalar_t__ likely (struct xfrm_state_afinfo const*) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 
 TYPE_3__* skb_dst (struct sk_buff*) ; 
 int stub1 (struct xfrm_state*,struct sk_buff*) ; 
 int /*<<< orphan*/  xfrm_af2proto (int /*<<< orphan*/ ) ; 
 struct xfrm_mode* xfrm_ip2inner_mode (struct xfrm_state*,int /*<<< orphan*/ ) ; 
 struct xfrm_state_afinfo* xfrm_state_afinfo_get_rcu (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int xfrm_inner_extract_output(struct xfrm_state *x, struct sk_buff *skb)
{
	const struct xfrm_state_afinfo *afinfo;
	const struct xfrm_mode *inner_mode;
	int err = -EAFNOSUPPORT;

	if (x->sel.family == AF_UNSPEC)
		inner_mode = xfrm_ip2inner_mode(x,
				xfrm_af2proto(skb_dst(skb)->ops->family));
	else
		inner_mode = &x->inner_mode;

	if (inner_mode == NULL)
		return -EAFNOSUPPORT;

	rcu_read_lock();
	afinfo = xfrm_state_afinfo_get_rcu(inner_mode->family);
	if (likely(afinfo))
		err = afinfo->extract_output(x, skb);
	rcu_read_unlock();

	return err;
}