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
struct TYPE_2__ {int encap; int /*<<< orphan*/  family; } ;
struct xfrm_state {TYPE_1__ outer_mode; } ;
struct sk_buff {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  AF_INET ; 
 int /*<<< orphan*/  AF_INET6 ; 
 int EOPNOTSUPP ; 
 int /*<<< orphan*/  WARN_ON_ONCE (int) ; 
#define  XFRM_MODE_BEET 131 
#define  XFRM_MODE_ROUTEOPTIMIZATION 130 
#define  XFRM_MODE_TRANSPORT 129 
#define  XFRM_MODE_TUNNEL 128 
 int xfrm4_prepare_output (struct xfrm_state*,struct sk_buff*) ; 
 int xfrm4_transport_output (struct xfrm_state*,struct sk_buff*) ; 
 int xfrm6_prepare_output (struct xfrm_state*,struct sk_buff*) ; 
 int xfrm6_ro_output (struct xfrm_state*,struct sk_buff*) ; 
 int xfrm6_transport_output (struct xfrm_state*,struct sk_buff*) ; 

__attribute__((used)) static int xfrm_outer_mode_output(struct xfrm_state *x, struct sk_buff *skb)
{
	switch (x->outer_mode.encap) {
	case XFRM_MODE_BEET:
	case XFRM_MODE_TUNNEL:
		if (x->outer_mode.family == AF_INET)
			return xfrm4_prepare_output(x, skb);
		if (x->outer_mode.family == AF_INET6)
			return xfrm6_prepare_output(x, skb);
		break;
	case XFRM_MODE_TRANSPORT:
		if (x->outer_mode.family == AF_INET)
			return xfrm4_transport_output(x, skb);
		if (x->outer_mode.family == AF_INET6)
			return xfrm6_transport_output(x, skb);
		break;
	case XFRM_MODE_ROUTEOPTIMIZATION:
		if (x->outer_mode.family == AF_INET6)
			return xfrm6_ro_output(x, skb);
		WARN_ON_ONCE(1);
		break;
	default:
		WARN_ON_ONCE(1);
		break;
	}

	return -EOPNOTSUPP;
}