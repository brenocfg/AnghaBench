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
typedef  int u8 ;
typedef  int /*<<< orphan*/  u32 ;
struct xfrm_state {int dummy; } ;
struct sk_buff {int dummy; } ;
struct dst_entry {struct xfrm_state* xfrm; } ;
struct common_audit_data {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  ASSOCIATION__SENDTO ; 
#define  IPPROTO_AH 130 
#define  IPPROTO_COMP 129 
#define  IPPROTO_ESP 128 
 int /*<<< orphan*/  SECCLASS_ASSOCIATION ; 
 int /*<<< orphan*/  SECINITSID_UNLABELED ; 
 int avc_has_perm (int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,int /*<<< orphan*/ ,struct common_audit_data*) ; 
 scalar_t__ selinux_authorizable_xfrm (struct xfrm_state*) ; 
 int /*<<< orphan*/  selinux_state ; 
 struct dst_entry* skb_dst (struct sk_buff*) ; 
 struct dst_entry* xfrm_dst_child (struct dst_entry*) ; 

int selinux_xfrm_postroute_last(u32 sk_sid, struct sk_buff *skb,
				struct common_audit_data *ad, u8 proto)
{
	struct dst_entry *dst;

	switch (proto) {
	case IPPROTO_AH:
	case IPPROTO_ESP:
	case IPPROTO_COMP:
		/* We should have already seen this packet once before it
		 * underwent xfrm(s). No need to subject it to the unlabeled
		 * check. */
		return 0;
	default:
		break;
	}

	dst = skb_dst(skb);
	if (dst) {
		struct dst_entry *iter;

		for (iter = dst; iter != NULL; iter = xfrm_dst_child(iter)) {
			struct xfrm_state *x = iter->xfrm;

			if (x && selinux_authorizable_xfrm(x))
				return 0;
		}
	}

	/* This check even when there's no association involved is intended,
	 * according to Trent Jaeger, to make sure a process can't engage in
	 * non-IPsec communication unless explicitly allowed by policy. */
	return avc_has_perm(&selinux_state, sk_sid, SECINITSID_UNLABELED,
			    SECCLASS_ASSOCIATION, ASSOCIATION__SENDTO, ad);
}