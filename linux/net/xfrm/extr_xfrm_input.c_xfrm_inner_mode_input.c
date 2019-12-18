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
struct xfrm_state {int dummy; } ;
struct xfrm_mode {int encap; int /*<<< orphan*/  family; } ;
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
 int xfrm4_transport_input (struct xfrm_state*,struct sk_buff*) ; 
 int xfrm6_transport_input (struct xfrm_state*,struct sk_buff*) ; 
 int xfrm_prepare_input (struct xfrm_state*,struct sk_buff*) ; 

__attribute__((used)) static int xfrm_inner_mode_input(struct xfrm_state *x,
				 const struct xfrm_mode *inner_mode,
				 struct sk_buff *skb)
{
	switch (inner_mode->encap) {
	case XFRM_MODE_BEET:
	case XFRM_MODE_TUNNEL:
		return xfrm_prepare_input(x, skb);
	case XFRM_MODE_TRANSPORT:
		if (inner_mode->family == AF_INET)
			return xfrm4_transport_input(x, skb);
		if (inner_mode->family == AF_INET6)
			return xfrm6_transport_input(x, skb);
		break;
	case XFRM_MODE_ROUTEOPTIMIZATION:
		WARN_ON_ONCE(1);
		break;
	default:
		WARN_ON_ONCE(1);
		break;
	}

	return -EOPNOTSUPP;
}