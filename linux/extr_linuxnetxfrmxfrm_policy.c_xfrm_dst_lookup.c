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
typedef  int /*<<< orphan*/  xfrm_address_t ;
typedef  int /*<<< orphan*/  u32 ;
struct TYPE_5__ {int /*<<< orphan*/  daddr; } ;
struct TYPE_4__ {int /*<<< orphan*/  saddr; } ;
struct xfrm_state {int /*<<< orphan*/ * coaddr; TYPE_3__* type; TYPE_2__ id; TYPE_1__ props; } ;
struct net {int dummy; } ;
struct dst_entry {int dummy; } ;
struct TYPE_6__ {int flags; } ;

/* Variables and functions */
 int /*<<< orphan*/  IS_ERR (struct dst_entry*) ; 
 int XFRM_TYPE_LOCAL_COADDR ; 
 int XFRM_TYPE_REMOTE_COADDR ; 
 struct dst_entry* __xfrm_dst_lookup (struct net*,int,int,int /*<<< orphan*/ *,int /*<<< orphan*/ *,int,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int) ; 
 struct net* xs_net (struct xfrm_state*) ; 

__attribute__((used)) static inline struct dst_entry *xfrm_dst_lookup(struct xfrm_state *x,
						int tos, int oif,
						xfrm_address_t *prev_saddr,
						xfrm_address_t *prev_daddr,
						int family, u32 mark)
{
	struct net *net = xs_net(x);
	xfrm_address_t *saddr = &x->props.saddr;
	xfrm_address_t *daddr = &x->id.daddr;
	struct dst_entry *dst;

	if (x->type->flags & XFRM_TYPE_LOCAL_COADDR) {
		saddr = x->coaddr;
		daddr = prev_daddr;
	}
	if (x->type->flags & XFRM_TYPE_REMOTE_COADDR) {
		saddr = prev_saddr;
		daddr = x->coaddr;
	}

	dst = __xfrm_dst_lookup(net, tos, oif, saddr, daddr, family, mark);

	if (!IS_ERR(dst)) {
		if (prev_saddr != saddr)
			memcpy(prev_saddr, saddr,  sizeof(*prev_saddr));
		if (prev_daddr != daddr)
			memcpy(prev_daddr, daddr,  sizeof(*prev_daddr));
	}

	return dst;
}