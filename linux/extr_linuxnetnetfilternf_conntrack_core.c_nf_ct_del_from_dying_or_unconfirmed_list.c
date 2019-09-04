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
struct nf_conn {TYPE_2__* tuplehash; int /*<<< orphan*/  cpu; } ;
struct ct_pcpu {int /*<<< orphan*/  lock; } ;
struct TYPE_4__ {int /*<<< orphan*/  pcpu_lists; } ;
struct TYPE_6__ {TYPE_1__ ct; } ;
struct TYPE_5__ {int /*<<< orphan*/  hnnode; } ;

/* Variables and functions */
 int /*<<< orphan*/  BUG_ON (int /*<<< orphan*/ ) ; 
 size_t IP_CT_DIR_ORIGINAL ; 
 int /*<<< orphan*/  hlist_nulls_del_rcu (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  hlist_nulls_unhashed (int /*<<< orphan*/ *) ; 
 TYPE_3__* nf_ct_net (struct nf_conn*) ; 
 struct ct_pcpu* per_cpu_ptr (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  spin_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  spin_unlock (int /*<<< orphan*/ *) ; 

__attribute__((used)) static void nf_ct_del_from_dying_or_unconfirmed_list(struct nf_conn *ct)
{
	struct ct_pcpu *pcpu;

	/* We overload first tuple to link into unconfirmed or dying list.*/
	pcpu = per_cpu_ptr(nf_ct_net(ct)->ct.pcpu_lists, ct->cpu);

	spin_lock(&pcpu->lock);
	BUG_ON(hlist_nulls_unhashed(&ct->tuplehash[IP_CT_DIR_ORIGINAL].hnnode));
	hlist_nulls_del_rcu(&ct->tuplehash[IP_CT_DIR_ORIGINAL].hnnode);
	spin_unlock(&pcpu->lock);
}