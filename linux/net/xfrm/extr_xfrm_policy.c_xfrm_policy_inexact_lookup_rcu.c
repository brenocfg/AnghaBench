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
typedef  int /*<<< orphan*/  u8 ;
typedef  int /*<<< orphan*/  u32 ;
typedef  int /*<<< orphan*/  u16 ;
struct xfrm_pol_inexact_key {int /*<<< orphan*/  net; int /*<<< orphan*/  if_id; int /*<<< orphan*/  dir; int /*<<< orphan*/  type; int /*<<< orphan*/  family; } ;
struct xfrm_pol_inexact_bin {int dummy; } ;
struct net {int dummy; } ;

/* Variables and functions */
 struct xfrm_pol_inexact_bin* rhashtable_lookup (int /*<<< orphan*/ *,struct xfrm_pol_inexact_key*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  write_pnet (int /*<<< orphan*/ *,struct net*) ; 
 int /*<<< orphan*/  xfrm_pol_inexact_params ; 
 int /*<<< orphan*/  xfrm_policy_inexact_table ; 

__attribute__((used)) static struct xfrm_pol_inexact_bin *
xfrm_policy_inexact_lookup_rcu(struct net *net, u8 type, u16 family,
			       u8 dir, u32 if_id)
{
	struct xfrm_pol_inexact_key k = {
		.family = family,
		.type = type,
		.dir = dir,
		.if_id = if_id,
	};

	write_pnet(&k.net, net);

	return rhashtable_lookup(&xfrm_policy_inexact_table, &k,
				 xfrm_pol_inexact_params);
}