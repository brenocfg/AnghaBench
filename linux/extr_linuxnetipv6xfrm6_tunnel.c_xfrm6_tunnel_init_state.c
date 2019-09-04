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
struct TYPE_2__ {scalar_t__ mode; int header_len; } ;
struct xfrm_state {TYPE_1__ props; scalar_t__ encap; } ;
struct ipv6hdr {int dummy; } ;

/* Variables and functions */
 int EINVAL ; 
 scalar_t__ XFRM_MODE_TUNNEL ; 

__attribute__((used)) static int xfrm6_tunnel_init_state(struct xfrm_state *x)
{
	if (x->props.mode != XFRM_MODE_TUNNEL)
		return -EINVAL;

	if (x->encap)
		return -EINVAL;

	x->props.header_len = sizeof(struct ipv6hdr);

	return 0;
}