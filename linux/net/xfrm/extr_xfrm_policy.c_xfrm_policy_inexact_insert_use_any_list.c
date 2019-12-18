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
struct TYPE_2__ {int /*<<< orphan*/  prefixlen_d; int /*<<< orphan*/  daddr; int /*<<< orphan*/  prefixlen_s; int /*<<< orphan*/  saddr; } ;
struct xfrm_policy {int /*<<< orphan*/  family; TYPE_1__ selector; } ;

/* Variables and functions */
 int xfrm_pol_inexact_addr_use_any_list (int /*<<< orphan*/  const*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static bool
xfrm_policy_inexact_insert_use_any_list(const struct xfrm_policy *policy)
{
	const xfrm_address_t *addr;
	bool saddr_any, daddr_any;
	u8 prefixlen;

	addr = &policy->selector.saddr;
	prefixlen = policy->selector.prefixlen_s;

	saddr_any = xfrm_pol_inexact_addr_use_any_list(addr,
						       policy->family,
						       prefixlen);
	addr = &policy->selector.daddr;
	prefixlen = policy->selector.prefixlen_d;
	daddr_any = xfrm_pol_inexact_addr_use_any_list(addr,
						       policy->family,
						       prefixlen);
	return saddr_any && daddr_any;
}