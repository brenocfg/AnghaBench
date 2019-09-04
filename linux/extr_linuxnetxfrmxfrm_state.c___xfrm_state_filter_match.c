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
struct TYPE_3__ {int /*<<< orphan*/  daddr; } ;
struct TYPE_4__ {scalar_t__ family; int /*<<< orphan*/  saddr; } ;
struct xfrm_state {TYPE_1__ id; TYPE_2__ props; } ;
struct xfrm_address_filter {scalar_t__ family; int /*<<< orphan*/  dplen; int /*<<< orphan*/  daddr; int /*<<< orphan*/  splen; int /*<<< orphan*/  saddr; } ;

/* Variables and functions */
 scalar_t__ AF_INET ; 
 scalar_t__ AF_INET6 ; 
 scalar_t__ addr_match (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool __xfrm_state_filter_match(struct xfrm_state *x,
				      struct xfrm_address_filter *filter)
{
	if (filter) {
		if ((filter->family == AF_INET ||
		     filter->family == AF_INET6) &&
		    x->props.family != filter->family)
			return false;

		return addr_match(&x->props.saddr, &filter->saddr,
				  filter->splen) &&
		       addr_match(&x->id.daddr, &filter->daddr,
				  filter->dplen);
	}
	return true;
}