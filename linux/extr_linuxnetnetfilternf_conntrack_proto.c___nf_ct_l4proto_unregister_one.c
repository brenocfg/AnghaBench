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
struct nf_conntrack_l4proto {size_t l3proto; size_t l4proto; } ;

/* Variables and functions */
 size_t ARRAY_SIZE (int /*<<< orphan*/ **) ; 
 int /*<<< orphan*/  BUG_ON (int) ; 
 int /*<<< orphan*/  lockdep_is_held (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nf_conntrack_l4proto_generic ; 
 int /*<<< orphan*/  nf_ct_proto_mutex ; 
 int /*<<< orphan*/ ** nf_ct_protos ; 
 int /*<<< orphan*/  rcu_assign_pointer (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 struct nf_conntrack_l4proto const* rcu_dereference_protected (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void __nf_ct_l4proto_unregister_one(const struct nf_conntrack_l4proto *l4proto)

{
	BUG_ON(l4proto->l3proto >= ARRAY_SIZE(nf_ct_protos));

	BUG_ON(rcu_dereference_protected(
			nf_ct_protos[l4proto->l3proto][l4proto->l4proto],
			lockdep_is_held(&nf_ct_proto_mutex)
			) != l4proto);
	rcu_assign_pointer(nf_ct_protos[l4proto->l3proto][l4proto->l4proto],
			   &nf_conntrack_l4proto_generic);
}