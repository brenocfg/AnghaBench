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
typedef  size_t u8 ;
struct nf_nat_l4proto {size_t l4proto; } ;

/* Variables and functions */
 int /*<<< orphan*/  RCU_INIT_POINTER (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nf_nat_l4proto_clean (size_t,size_t) ; 
 int /*<<< orphan*/  nf_nat_l4proto_unknown ; 
 int /*<<< orphan*/ ** nf_nat_l4protos ; 
 int /*<<< orphan*/  nf_nat_proto_mutex ; 
 int /*<<< orphan*/  synchronize_rcu () ; 

void nf_nat_l4proto_unregister(u8 l3proto, const struct nf_nat_l4proto *l4proto)
{
	mutex_lock(&nf_nat_proto_mutex);
	RCU_INIT_POINTER(nf_nat_l4protos[l3proto][l4proto->l4proto],
			 &nf_nat_l4proto_unknown);
	mutex_unlock(&nf_nat_proto_mutex);
	synchronize_rcu();

	nf_nat_l4proto_clean(l3proto, l4proto->l4proto);
}