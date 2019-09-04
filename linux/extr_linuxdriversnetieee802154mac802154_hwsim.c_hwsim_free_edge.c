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
struct hwsim_edge_info {int /*<<< orphan*/  info; } ;
struct hwsim_edge {int /*<<< orphan*/  info; } ;

/* Variables and functions */
 int /*<<< orphan*/  kfree_rcu (struct hwsim_edge_info*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu ; 
 struct hwsim_edge_info* rcu_dereference (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  rcu_read_lock () ; 
 int /*<<< orphan*/  rcu_read_unlock () ; 

__attribute__((used)) static void hwsim_free_edge(struct hwsim_edge *e)
{
	struct hwsim_edge_info *einfo;

	rcu_read_lock();
	einfo = rcu_dereference(e->info);
	rcu_read_unlock();

	kfree_rcu(einfo, rcu);
	kfree_rcu(e, rcu);
}