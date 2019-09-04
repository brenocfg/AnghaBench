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
struct TYPE_5__ {int /*<<< orphan*/  flags; } ;
struct xfrm_state {TYPE_2__ props; } ;
struct TYPE_4__ {scalar_t__ sysctl_ip_no_pmtu_disc; } ;
struct TYPE_6__ {TYPE_1__ ipv4; } ;

/* Variables and functions */
 int /*<<< orphan*/  XFRM_STATE_NOPMTUDISC ; 
 TYPE_3__* xs_net (struct xfrm_state*) ; 

__attribute__((used)) static int xfrm4_init_flags(struct xfrm_state *x)
{
	if (xs_net(x)->ipv4.sysctl_ip_no_pmtu_disc)
		x->props.flags |= XFRM_STATE_NOPMTUDISC;
	return 0;
}