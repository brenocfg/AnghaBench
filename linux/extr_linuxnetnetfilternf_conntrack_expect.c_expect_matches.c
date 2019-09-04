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
struct nf_conntrack_expect {scalar_t__ master; int /*<<< orphan*/  mask; int /*<<< orphan*/  tuple; } ;

/* Variables and functions */
 scalar_t__ net_eq (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  nf_ct_net (scalar_t__) ; 
 scalar_t__ nf_ct_tuple_equal (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 scalar_t__ nf_ct_tuple_mask_equal (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nf_ct_zone (scalar_t__) ; 
 scalar_t__ nf_ct_zone_equal_any (scalar_t__,int /*<<< orphan*/ ) ; 

__attribute__((used)) static inline int expect_matches(const struct nf_conntrack_expect *a,
				 const struct nf_conntrack_expect *b)
{
	return a->master == b->master &&
	       nf_ct_tuple_equal(&a->tuple, &b->tuple) &&
	       nf_ct_tuple_mask_equal(&a->mask, &b->mask) &&
	       net_eq(nf_ct_net(a->master), nf_ct_net(b->master)) &&
	       nf_ct_zone_equal_any(a->master, nf_ct_zone(b->master));
}