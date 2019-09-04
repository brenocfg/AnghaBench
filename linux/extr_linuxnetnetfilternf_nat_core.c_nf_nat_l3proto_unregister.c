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
struct nf_nat_l3proto {size_t l3proto; } ;

/* Variables and functions */
 int /*<<< orphan*/  RCU_INIT_POINTER (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nf_nat_l3proto_clean (size_t) ; 
 int /*<<< orphan*/ * nf_nat_l3protos ; 
 int /*<<< orphan*/  nf_nat_proto_mutex ; 
 int /*<<< orphan*/  synchronize_rcu () ; 

void nf_nat_l3proto_unregister(const struct nf_nat_l3proto *l3proto)
{
	mutex_lock(&nf_nat_proto_mutex);
	RCU_INIT_POINTER(nf_nat_l3protos[l3proto->l3proto], NULL);
	mutex_unlock(&nf_nat_proto_mutex);
	synchronize_rcu();

	nf_nat_l3proto_clean(l3proto->l3proto);
}