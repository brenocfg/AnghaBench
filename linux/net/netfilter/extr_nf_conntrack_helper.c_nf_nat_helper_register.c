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
struct nf_conntrack_nat_helper {int /*<<< orphan*/  list; } ;

/* Variables and functions */
 int /*<<< orphan*/  list_add_rcu (int /*<<< orphan*/ *,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_lock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  mutex_unlock (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  nf_ct_nat_helpers ; 
 int /*<<< orphan*/  nf_ct_nat_helpers_mutex ; 

void nf_nat_helper_register(struct nf_conntrack_nat_helper *nat)
{
	mutex_lock(&nf_ct_nat_helpers_mutex);
	list_add_rcu(&nat->list, &nf_ct_nat_helpers);
	mutex_unlock(&nf_ct_nat_helpers_mutex);
}