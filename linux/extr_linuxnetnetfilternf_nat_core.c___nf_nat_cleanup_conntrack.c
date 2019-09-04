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
struct nf_conn {int /*<<< orphan*/  nat_bysource; TYPE_1__* tuplehash; } ;
struct TYPE_2__ {int /*<<< orphan*/  tuple; } ;

/* Variables and functions */
 unsigned int CONNTRACK_LOCKS ; 
 size_t IP_CT_DIR_ORIGINAL ; 
 unsigned int hash_by_src (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hlist_del_rcu (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nf_ct_net (struct nf_conn*) ; 
 int /*<<< orphan*/ * nf_nat_locks ; 
 int /*<<< orphan*/  spin_lock_bh (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock_bh (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void __nf_nat_cleanup_conntrack(struct nf_conn *ct)
{
	unsigned int h;

	h = hash_by_src(nf_ct_net(ct), &ct->tuplehash[IP_CT_DIR_ORIGINAL].tuple);
	spin_lock_bh(&nf_nat_locks[h % CONNTRACK_LOCKS]);
	hlist_del_rcu(&ct->nat_bysource);
	spin_unlock_bh(&nf_nat_locks[h % CONNTRACK_LOCKS]);
}